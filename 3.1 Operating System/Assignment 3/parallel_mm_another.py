"""
Matrix Multiplication with Continuous CPU Utilization Display
"""

import multiprocessing
import sys
import time
import subprocess

# Auto-install numpy if not present
try:
    import numpy as np
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "numpy"])
    import numpy as np


# ---------------- CPU Monitoring ----------------
def start_cpu_monitor():
    try:
        # Try cpustat first (sample every 1 second)
        proc = subprocess.Popen(["cpustat", "-c", "1"])
        return proc
    except FileNotFoundError:
        print("[INFO] cpustat not found, trying sar...")
        try:
            # sar 1 → sample every 1 second continuously
            proc = subprocess.Popen(["sar", "1"])
            return proc
        except FileNotFoundError:
            print("[WARNING] Neither cpustat nor sar found. CPU monitoring disabled.")
            return None

def stop_cpu_monitor(proc):
    if proc:
        proc.terminate()


# ---------------- Matrix Multiplication ----------------
s = sys.argv
if len(s) < 5:
    print(f"Required 4 arguments. You entered {len(s)}")
    sys.exit(1)

MAX = int(s[1])
MAX_PROCESS = int(s[2])
MOD = int(s[3])
MAX_VAL = 100000
print_switch = int(s[4])

# Generate random matrices using NumPy
matA = np.random.randint(0, MOD, size=(MAX, MAX), dtype=np.int64)
matB = np.random.randint(0, MOD, size=(MAX, MAX), dtype=np.int64)

def printMatrix(mat):
    for i in range(min(20, mat.shape[0])):
        for j in range(min(20, mat.shape[1])):
            print(f"{mat[i, j]:5d}", end=" ")
        print()
    print("Truncated for display... (showing first 20 rows and columns)")

def multi(args):
    row_index, A, B = args
    row_result = A[row_index, :].dot(B)
    return (row_index, row_result)

if __name__ == "__main__":
    if print_switch == 1:
        print("Matrix A")
        printMatrix(matA)
        print("Matrix B")
        printMatrix(matB)
        print("\n\nCOMPUTING MULTIPLICATION...")

    # Start CPU monitoring
    cpu_proc = start_cpu_monitor()

    args = [(i, matA, matB) for i in range(MAX)]
    pool = multiprocessing.Pool(processes=MAX_PROCESS)

    start_time = time.perf_counter()
    results = pool.map(multi, args)
    pool.close()
    pool.join()
    end_time = time.perf_counter()

    matC = np.zeros((MAX, MAX), dtype=np.int64)
    for row_index, row_result in results:
        matC[row_index, :] = row_result

    # Stop CPU monitoring
    stop_cpu_monitor(cpu_proc)

    print("Matrix C = A x B (mod {}) =".format(MOD))
    printMatrix(matC % MOD)  # apply modulus before displaying


    elapsed_time = end_time - start_time
    print(f"\n\nTIME TAKEN IS {elapsed_time:.6f} SECONDS")


