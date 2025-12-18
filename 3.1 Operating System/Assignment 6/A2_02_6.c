/*
===========================================================================
Matrix multiplication with pthreads (unsigned char matrices)
===========================================================================
*/

/*  
adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Documents/Unknown$ gcc -pthread -o prog A2_02_6.c 
adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Documents/Unknown$ ./prog 3000 4 1000 0
Multiplication time: 11.294785 sec
adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Documents/Unknown$

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
  3.00   2.00   1.00	1497 S	5   1.49m /usr/lib/xorg/Xorg
  2.00   2.00   0.00	4076 S	1  26.46s /usr/libexec/gnome-terminal-server
  2.00   1.00   1.00	1627 S	3   2.46m /usr/bin/gnome-shell
  1.00   1.00   0.00	3629 S	6   6.35m /usr/lib/firefox/firefox
  1.00   1.00   0.00	3356 S	8   3.07s /usr/lib/firefox/firefox

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
398.00 398.00   0.00   10421 S	9   5.26s ./prog
  1.00   1.00   0.00	4076 S	1  26.47s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]
  1.00   0.00   1.00	1497 S	5   1.49m /usr/lib/xorg/Xorg
  1.00   1.00   0.00	1811 S	6   4.87s /usr/libexec/gsd-media-keys
  1.00   1.00   0.00	1627 S	3   2.46m /usr/bin/gnome-shell

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9   9.26s ./prog
  5.00   4.00   1.00	3282 S	6   6.59m /usr/lib/firefox/firefox
  1.00   1.00   0.00  	14 I	2   4.46s [rcu_sched]
  1.00   0.00   1.00 	805 S	2  18.50s avahi-daemon: running [adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC-6.local]
  1.00   1.00   0.00	4076 S	1  26.48s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]
  1.00   1.00   0.00	1497 S	5   1.49m /usr/lib/xorg/Xorg
  1.00   1.00   0.00	3529 S	5   1.58m /usr/lib/firefox/firefox
  1.00   1.00   0.00	1627 S	3   2.46m /usr/bin/gnome-shell
  1.00   0.00   1.00	3629 S	6   6.35m /usr/lib/firefox/firefox

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  13.26s ./prog
  2.00   1.00   1.00	1497 S	5   1.49m /usr/lib/xorg/Xorg
  1.00   0.00   1.00  	69 S	9   0.15s [migration/9]
  1.00   0.00   1.00	3963 S   10  31.67s /usr/lib/firefox/firefox
  1.00   1.00   0.00	3629 S	6   6.35m /usr/lib/firefox/firefox

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  17.26s ./prog
  3.00   2.00   1.00	1627 S	3   2.46m /usr/bin/gnome-shell
  1.00   1.00   0.00	4076 S	1  26.49s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00   10104 R   10   1.42s cpustat
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]
  1.00   1.00   0.00	1497 S	5   1.49m /usr/lib/xorg/Xorg

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  21.26s ./prog
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  25.26s ./prog
  2.00   1.00   1.00	4076 S	1  26.51s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]
  1.00   0.00   1.00	1497 S	5   1.49m /usr/lib/xorg/Xorg
  1.00   1.00   0.00	3282 S	6   6.59m /usr/lib/firefox/firefox
  1.00   1.00   0.00	1627 S	3   2.46m /usr/bin/gnome-shell

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  29.26s ./prog
  2.00   1.00   1.00	1497 S	5   1.49m /usr/lib/xorg/Xorg

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  33.26s ./prog
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]
  1.00   1.00   0.00	3282 S	6   6.59m /usr/lib/firefox/firefox
  1.00   1.00   0.00	1627 S	3   2.46m /usr/bin/gnome-shell

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  37.26s ./prog
  1.00   1.00   0.00	1497 S	5   1.49m /usr/lib/xorg/Xorg

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
400.00 400.00   0.00   10421 S	9  41.26s ./prog
  1.00   0.00   1.00	1481 S   10   6.14s /usr/bin/pulseaudio
  1.00   1.00   0.00	9374 S	6   6.41s /usr/lib/firefox/firefox
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
383.00 383.00   0.00   10421 S	9  45.09s ./prog
  1.00   0.00   1.00   10104 R   10   1.43s cpustat
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]

  %CPU   %USR   %SYS 	PID S  CPU	Time Task
  1.00   0.00   1.00	9374 S	6   6.42s /usr/lib/firefox/firefox
  1.00   1.00   0.00	4076 S	1  26.52s /usr/libexec/gnome-terminal-server
  1.00   0.00   1.00 	565 S	9   1.32m [irq/162-rtw88_p]
  1.00   1.00   0.00	3963 S   10  31.68s /usr/lib/firefox/firefox
  1.00   1.00   0.00	1627 S	3   2.46m /usr/bin/gnome-shell


adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/Documents/Unknown$ ps -eLf | grep prog
adminpc	10421	5076   10421  5	5 13:33 pts/3	00:00:00 ./prog 3000 4 1000 0
adminpc	10421	5076   10426 99	5 13:33 pts/3	00:00:01 ./prog 3000 4 1000 0
adminpc	10421	5076   10427 99	5 13:33 pts/3	00:00:01 ./prog 3000 4 1000 0
adminpc	10421	5076   10428 99	5 13:33 pts/3	00:00:01 ./prog 3000 4 1000 0
adminpc	10421	5076   10429 99	5 13:33 pts/3	00:00:01 ./prog 3000 4 1000 0
adminpc	10431	9741   10431  0	1 13:33 pts/4	00:00:00 grep --color=auto prog

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <time.h>

/*-------------------------------------------------------------
  (1) Structure to pass arguments to each thread
-------------------------------------------------------------*/
typedef struct {
    int tid;                 // Thread ID
    int start_row;           // Start row (inclusive)
    int end_row;             // End row (exclusive)
    int N;                   // Matrix size
    const unsigned char *A;  // Pointer to matrix A
    const unsigned char *B_t;// Pointer to transposed matrix B
    unsigned int *C;         // Pointer to result matrix C
} thread_arg_t;

/*-------------------------------------------------------------
  (2) Thread worker function: computes rows [start_row, end_row)
-------------------------------------------------------------*/
void *thread_mul(void *arg_v) {
    thread_arg_t *arg = (thread_arg_t *)arg_v;
    int N = arg->N;
    const unsigned char *A = arg->A;
    const unsigned char *B_t = arg->B_t;
    unsigned int *C = arg->C;

    int i, j, k;
    for (i = arg->start_row; i < arg->end_row; ++i) {
        const unsigned char *rowA = A + (size_t)i * N;
        unsigned int *rowC = C + (size_t)i * N;
        for (j = 0; j < N; ++j) {
            const unsigned char *colB = B_t + (size_t)j * N;
            unsigned int sum = 0;
            for (k = 0; k < N; ++k) {
                sum += (unsigned int)rowA[k] * (unsigned int)colB[k];
            }
            rowC[j] = sum;
        }
    }
    return NULL;
}

/*-------------------------------------------------------------
  (3) Utility: Print unsigned char matrix (A or B)
-------------------------------------------------------------*/
void print_matrix_uc(const unsigned char *M, int N, const char *name) {
    int i, j;
    printf("Matrix %s (%d x %d):\n", name, N, N);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%3u ", (unsigned)M[(size_t)i * N + j]);
        }
        printf("\n");
    }
}

/*-------------------------------------------------------------
  (4) Utility: Print unsigned int matrix (C)
-------------------------------------------------------------*/
void print_matrix_ui(const unsigned int *M, int N, const char *name) {
    int i, j;
    printf("Matrix %s (%d x %d):\n", name, N, N);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%10u ", (unsigned)M[(size_t)i * N + j]);
        }
        printf("\n");
    }
}

/*-------------------------------------------------------------
  (5) Main program
-------------------------------------------------------------*/
int main(int argc, char **argv) {
    // (5.1) Parse arguments
    
    
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <N> <num_threads> <mod> <print_switch>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    // convert to long
    
    
    long N_long = strtol(argv[1], NULL, 10);
    long num_threads_long = strtol(argv[2], NULL, 10);
    long mod_long = strtol(argv[3], NULL, 10);
    long print_switch_long = strtol(argv[4], NULL, 10);


    if (errno || N_long <= 0 || num_threads_long <= 0 || mod_long <= 0) {
        fprintf(stderr, "Invalid numeric argument.\n");
        return EXIT_FAILURE;
    }

    int N = (int)N_long;
    int num_threads = (int)num_threads_long;
    int mod = (int)mod_long;
    int print_switch = (int)print_switch_long;

    if (num_threads > N) {
        num_threads = N;  // Limit threads to rows if given more than no. of rows
    }

    //printf("Matrix size: %d x %d\nThreads: %d\nmod: %d\nprint_switch: %d\n",
           //N, N, num_threads, mod, print_switch);

    // (5.2) Memory allocation
    size_t elems = (size_t)N * (size_t)N;
    size_t bytes_A = elems * sizeof(unsigned char);
    size_t bytes_B = elems * sizeof(unsigned char);
    size_t bytes_Bt = elems * sizeof(unsigned char);
    size_t bytes_C = elems * sizeof(unsigned int);

    //printf("Memory estimate: total %.2f MB\n",
           //(bytes_A + bytes_B + bytes_Bt + bytes_C) / (1024.0*1024.0));

    unsigned char *A = (unsigned char *)malloc(bytes_A);
    unsigned char *B = (unsigned char *)malloc(bytes_B);
    unsigned char *B_t = (unsigned char *)malloc(bytes_Bt);
    unsigned int *C = (unsigned int *)malloc(bytes_C);

    if (!A || !B || !B_t || !C) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    // (5.3) Fill matrices with random numbers [0, mod)
    srand((unsigned)time(NULL));
    size_t i, j;
    for (i = 0; i < elems; ++i) {
        A[i] = (unsigned char)(rand() % mod);
        B[i] = (unsigned char)(rand() % mod);
    }

    // (5.4) Transpose B into B_t for cache efficiency
    for (i = 0; i < (size_t)N; ++i) {
        for (j = 0; j < (size_t)N; ++j) {
            B_t[j * (size_t)N + i] = B[i * (size_t)N + j];
        }
    }

    // (5.5) Optional: print matrices A and B (only if small)
    if (print_switch && N <= 16) {
        print_matrix_uc(A, N, "A");
        print_matrix_uc(B, N, "B");
    }

    // (5.6) Setup threads
    pthread_t *threads = malloc(sizeof(pthread_t) * (size_t)num_threads);
    thread_arg_t *targs = malloc(sizeof(thread_arg_t) * (size_t)num_threads);
    memset(C, 0, bytes_C);

    int rows_per_thread = N / num_threads;
    int extra = N % num_threads;



    // **********start time calculation**********************
    
    struct timeval tstart, tend;
    gettimeofday(&tstart, NULL);

    // (5.7) Create threads
    int current_row = 0;
    int t;
    for (t = 0; t < num_threads; ++t) {
        int start = current_row;
        int rows = rows_per_thread + (t < extra ? 1 : 0);
        int end = start + rows;
        current_row = end;

        targs[t].tid = t;
        targs[t].start_row = start;
        targs[t].end_row = end;
        targs[t].N = N;
        targs[t].A = A;
        targs[t].B_t = B_t;
        targs[t].C = C;

        pthread_create(&threads[t], NULL, thread_mul, &targs[t]);
    }

    // (5.8) Join threads
    for (t = 0; t < num_threads; ++t) {
        pthread_join(threads[t], NULL);
    }


    // **********end time calculation******************
    gettimeofday(&tend, NULL);

    // (5.9) Measure execution time
    long sec = tend.tv_sec - tstart.tv_sec;
    long usec = tend.tv_usec - tstart.tv_usec;
    if (usec < 0) { sec--; usec += 1000000; }
    double elapsed = sec + usec / 1e6;

    printf("Multiplication time: %.6f sec\n", elapsed);

    // (5.10) Optional: print result
    if (print_switch) {
        print_matrix_ui(C, N, "Result C");
    }

    // (5.11) Cleanup
    free(A); free(B); free(B_t); free(C);
    free(threads); free(targs);

    return EXIT_SUCCESS;
}

