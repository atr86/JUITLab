#!/usr/bin/env python3
"""
Parallel Matrix Multiplication (A[NxN] x B[NxN] = C[NxN]) using multiprocessing.

Command-line args:
  1) N               : dimension (e.g., 3000)
  2) P               : number of processes (e.g., 1..CPU count)
  3) MOD             : modulus to init A and B with unsigned integers in [0, MOD)
  4) print_switch    : 1 -> print A, B, C (truncated if large); 0 -> don't print

Requirements fulfilled:
- Uses multiprocessing only (no threading module).
- Times ONLY the multiplication step with time.perf_counter().
- Initializes A and B with random unsigned ints modulo MOD.
- Shows CPU utilization via mpstat or sar if available.
- Dynamically allocates memory; handles large N (e.g., 3000), subject to RAM limits.

Implementation details:
- If NumPy is available: uses shared_memory + NumPy arrays for storage and per-process
  row-chunk matmul with BLAS threading disabled (so increasing P improves timing).
- If NumPy is NOT available: falls back to pure-stdlib shared arrays (multiprocessing.Array)
  and a naïve triple loop per-process (suitable for smaller N; very slow for N~3000).
"""

import argparse
import os
import sys
import time
import math
import random
import shutil
import subprocess
import multiprocessing as mp

# Try NumPy; if available we'll use it for array storage & compute.
USE_NUMPY = True
try:
    # Disable internal BLAS threading so multiprocessing scaling is visible
    os.environ.setdefault("OMP_NUM_THREADS", "1")
    os.environ.setdefault("OPENBLAS_NUM_THREADS", "1")
    os.environ.setdefault("MKL_NUM_THREADS", "1")
    import numpy as np
    from multiprocessing import shared_memory
except Exception:
    USE_NUMPY = False

# ----------------------- Common utilities -----------------------

def maybe_start_cpu_monitor():
    """Start mpstat or sar to capture CPU usage at 1-second intervals; return (proc, tool) or (None, None)."""
    if shutil.which("mpstat"):
        proc = subprocess.Popen(["mpstat", "-P", "ALL", "1"],
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        return proc, "mpstat"
    if shutil.which("sar"):
        proc = subprocess.Popen(["sar", "-P", "ALL", "1"],
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        return proc, "sar"
    return None, None

def stop_cpu_monitor(proc):
    if proc is None:
        return None
    try:
        proc.terminate()
        try:
            proc.wait(timeout=3)
        except subprocess.TimeoutExpired:
            proc.kill()
        return proc.stdout.read() if proc.stdout else ""
    except Exception:
        return None

def pretty_print_matrix(name, getter, N, max_rows=20, max_cols=20):
    """Print small matrices fully; otherwise show a truncated top-left block using getter(i,j)->int."""
    print(f"\n{name} [{N} x {N}]")
    r = min(N, max_rows); c = min(N, max_cols)
    # Render small slice
    for i in range(r):
        row = [str(getter(i, j)) for j in range(c)]
        print(" ".join(row))
    if N > r or N > c:
        print(f"... truncated ({N - r} more rows, {N - c} more cols)")

# ----------------------- NumPy-backed path -----------------------

_np_ctx = {"A": None, "B": None, "C": None, "N": None}

def _np_init(N, A_name, B_name, C_name, shape, dtype_str):
    """Initializer: attach to shared memory blocks for NumPy path."""
    dtype = np.dtype(dtype_str)
    _np_ctx["N"] = N
    _np_ctx["A_shm"] = shared_memory.SharedMemory(name=A_name)
    _np_ctx["B_shm"] = shared_memory.SharedMemory(name=B_name)
    _np_ctx["C_shm"] = shared_memory.SharedMemory(name=C_name)
    _np_ctx["A"] = np.ndarray(shape, dtype=dtype, buffer=_np_ctx["A_shm"].buf, order="C")
    _np_ctx["B"] = np.ndarray(shape, dtype=dtype, buffer=_np_ctx["B_shm"].buf, order="C")
    _np_ctx["C"] = np.ndarray(shape, dtype=dtype, buffer=_np_ctx["C_shm"].buf, order="C")

def _np_work_chunk(row_start, row_end):
    """Compute C[row_start:row_end, :] = A[row_start:row_end, :] @ B using NumPy (threads disabled)."""
    A = _np_ctx["A"]; B = _np_ctx["B"]; C = _np_ctx["C"]
    C[row_start:row_end, :] = A[row_start:row_end, :].dot(B)

# ----------------------- Pure stdlib path -----------------------

_py_ctx = {"A": None, "B": None, "C": None, "N": None}

def _py_init(N, A_base, B_base, C_base):
    """Initializer: set globals to shared ctypes arrays for pure-Python path."""
    _py_ctx["N"] = N
    _py_ctx["A"] = A_base
    _py_ctx["B"] = B_base
    _py_ctx["C"] = C_base

def _py_work_chunk(row_start, row_end):
    """Triple-loop multiply for rows in [row_start, row_end). VERY SLOW for huge N."""
    A = _py_ctx["A"]; B = _py_ctx["B"]; C = _py_ctx["C"]; N = _py_ctx["N"]
    for i in range(row_start, row_end):
        base_i = i * N
        for k in range(N):
            acc = 0
            for j in range(N):
                acc += A[base_i + j] * B[j * N + k]
            C[base_i + k] = acc  # will wrap if using c_uint

# ----------------------- Main -----------------------

def main():
    parser = argparse.ArgumentParser(description="Parallel matrix multiply using multiprocessing (NumPy if available).")
    parser.add_argument("N", type=int, help="Matrix dimension (e.g., 3000)")
    parser.add_argument("P", type=int, help="Number of processes")
    parser.add_argument("MOD", type=int, help="Modulus for initializing A and B (values in [0, MOD))")
    parser.add_argument("print_switch", type=int, choices=[0,1], help="1 to print matrices; 0 to suppress printing")
    args = parser.parse_args()

    N = args.N
    P = max(1, args.P)
    MOD = max(1, args.MOD)
    print_switch = args.print_switch

    # Choose unsigned storage size based on MOD
    # Use 32-bit if MOD <= 2**32-1, else 64-bit.
    use_64 = MOD > 0xFFFFFFFF
    if USE_NUMPY:
        dtype = np.uint64 if use_64 else np.uint32
        shape = (N, N)

        # Initialize (not timed)
        rng = np.random.default_rng()
        A_local = rng.integers(0, MOD, size=shape, dtype=dtype)
        B_local = rng.integers(0, MOD, size=shape, dtype=dtype)

        # Create shared memory blocks
        A_shm = shared_memory.SharedMemory(create=True, size=A_local.nbytes)
        B_shm = shared_memory.SharedMemory(create=True, size=B_local.nbytes)
        C_shm = shared_memory.SharedMemory(create=True, size=A_local.nbytes)
        try:
            A = np.ndarray(shape, dtype=dtype, buffer=A_shm.buf, order="C")
            B = np.ndarray(shape, dtype=dtype, buffer=B_shm.buf, order="C")
            C = np.ndarray(shape, dtype=dtype, buffer=C_shm.buf, order="C")
            A[...] = A_local
            B[...] = B_local
            C.fill(0)

            if print_switch == 1:
                def getA(i,j): return int(A[i,j])
                def getB(i,j): return int(B[i,j])
                pretty_print_matrix("Matrix A", getA, N)
                pretty_print_matrix("Matrix B", getB, N)

            # Build row-chunk tasks
            rows_per = math.ceil(N / P)
            tasks = [(i*rows_per, min(N, (i+1)*rows_per)) for i in range(P) if i*rows_per < N]

            # Optional CPU monitor
            mon_proc, mon_tool = maybe_start_cpu_monitor()

            t0 = time.perf_counter()
            # Real starmap call (kept separate to avoid linter confusion above)
            with mp.Pool(processes=P,
                         initializer=_np_init,
                         initargs=(N, A_shm.name, B_shm.name, C_shm.name, shape, A.dtype.str)) as pool:
                pool.starmap(_np_work_chunk, tasks)
            t1 = time.perf_counter()

            mon_out = stop_cpu_monitor(mon_proc)
            elapsed = t1 - t0

            print("----- Assignment Timing & CPU Utilization -----")
            print(f"N={N}, P={P}, MOD={MOD}, print_switch={print_switch}")
            print(f"Elapsed (multiplication only): {elapsed:.6f} seconds")
            if mon_out:
                print("CPU utilization (captured while computing):")
                print(mon_out.strip())
            else:
                print("CPU utilization: mpstat/sar not found on PATH; skipping.")
            print("------------------------------------------------")

            if print_switch == 1:
                def getC(i,j): return int(C[i,j])
                pretty_print_matrix("Matrix C = A x B", getC, N)

        finally:
            # Clean up shared memory
            try:
                A_shm.close(); B_shm.close(); C_shm.close()
            except Exception:
                pass
            try:
                A_shm.unlink(); B_shm.unlink(); C_shm.unlink()
            except Exception:
                pass

    else:
        # Pure stdlib path
        # Choose ctypes type based on width
        from ctypes import c_uint32, c_uint64
        c_uint = c_uint64 if use_64 else c_uint32

        # Shared flat arrays of length N*N
        size = N * N
        A = mp.Array(c_uint, size, lock=False)
        B = mp.Array(c_uint, size, lock=False)
        C = mp.Array(c_uint, size, lock=False)

        # Initialize (not timed)
        for i in range(size):
            A[i] = random.randrange(MOD)
            B[i] = random.randrange(MOD)
            C[i] = 0

        if print_switch == 1:
            def getA(i,j): return int(A[i*N + j])
            def getB(i,j): return int(B[i*N + j])
            pretty_print_matrix("Matrix A", getA, N)
            pretty_print_matrix("Matrix B", getB, N)

        rows_per = math.ceil(N / P)
        tasks = [(i*rows_per, min(N, (i+1)*rows_per)) for i in range(P) if i*rows_per < N]

        mon_proc, mon_tool = maybe_start_cpu_monitor()

        # Warn if too big without NumPy (to avoid hours-long run)
        if N >= 1500:
            print("WARNING: NumPy not found; pure-Python multiply for N>=1500 will be extremely slow.", file=sys.stderr)

        t0 = time.perf_counter()
        with mp.Pool(processes=P, initializer=_py_init, initargs=(N, A, B, C)) as pool:
            pool.starmap(_py_work_chunk, tasks)
        t1 = time.perf_counter()

        mon_out = stop_cpu_monitor(mon_proc)
        elapsed = t1 - t0

        print("----- Assignment Timing & CPU Utilization -----")
        print(f"N={N}, P={P}, MOD={MOD}, print_switch={print_switch}")
        print(f"Elapsed (multiplication only): {elapsed:.6f} seconds")
        if mon_out:
            print("CPU utilization (captured while computing):")
            print(mon_out.strip())
        else:
            print("CPU utilization: mpstat/sar not found on PATH; skipping.")
        print("------------------------------------------------")

        if print_switch == 1:
            def getC(i,j): return int(C[i*N + j])
            pretty_print_matrix("Matrix C = A x B", getC, N)

if __name__ == "__main__":
    if sys.platform.startswith("win"):
        mp.set_start_method("spawn", force=True)
    main()
