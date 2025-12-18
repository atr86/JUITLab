/*
 *
 * 3rd Year 1st Semester OS Lab - Information Technology
 * Section: A2
 * Team Number: 02
 *    Team Member Names                   Roll Numbers
 * 1. Abishkar Chatterjee (Team Leader) - 002311001080
 * 2. Atrij Roy                         - 002311001086
 * 3. Soyeb Hoque                       - 002311001065
 *
 * Assignment: 5 (10 Marks) [CO4 & CO5]
 * Title: Thread, Synchronizations & Shared Memory
 * Description: Consider a main process which creates three threads Th1, Th2, and Th3. The main
 * process also creates two random quantities (X, Y), both less than 10. These two values will be placed
 * by the main process in the shared memory (One variant of IPC Primitive) that is accessible by all the three threads Th1, Th2 and Th3. The shared
 * memory will be created by the main process using shmat/shmget calls.
 * For each pair of values (X,Y), it is required that some computations should be done by various threads. The thread Th1 will compute A (X*Y), the thread Th2 will
 * compute B (2*X+2*Y+1) and Th3 computes C (B/A). All these values are kept in the shared memory in a tabular fashion as shown below.
 * The number of (X,Y) pairs will be taken as an argument from the CLI. It is the responsibility of the main process to populate required numbers of (X,Y)s in the
 * shared memory. The program will only exit when all A,B,C are computed for all given (X,Y) values. Before exiting, all (X,Y)s, As, Bs and Cs should be displayed as per the
 * format shown below.
 * Whenever, the threads complete one phase of computations (A, B and C), they will go for another pair of (X,Y) values; but they will start all together. This can be
 * achieved by proper synchronization.
 * Use the proper shell command(ipcs or simmilar) to display the Shared Memory
 * Status/Info/Statistics and attach this sample output as a part of the starting comment
 * block. This statistics should show the Shared Memory which your program has created.
 *
 * Command Line Inputs Required:
 * N, the number of pairs of (X,Y) to be generated.
 * NOTE: In this program the max value of N is at 100000 so N should be between 1 to 100000.

 * Sample Output Generated:
 * For inputs:
 * N = 20
 *
 * ===== OUTPUT =====
 *
 * Pairs(X,Y) |   A   |   B   |    C
 * -------------------------------------
 * (8,6)    | 48    | 29    | 0.60
 * (9,9)    | 81    | 37    | 0.00
 * (9,0)    | 0     | 19    | 0.00
 * (2,8)    | 16    | 21    | 1.31
 * (7,0)    | 0     | 15    | 0.00
 * (0,0)    | 0     | 1     | 0.00
 * (8,3)    | 24    | 23    | 0.00
 * (8,1)    | 8     | 19    | 0.00
 * (7,1)    | 7     | 17    | 0.00
 * (9,1)    | 9     | 21    | 2.33
 * (9,2)    | 18    | 23    | 0.00
 * (7,6)    | 42    | 27    | 0.64
 * (1,0)    | 0     | 3     | 0.00
 * (3,4)    | 12    | 15    | 0.00
 * (3,4)    | 12    | 15    | 1.25
 * (3,3)    | 9     | 13    | 1.44
 * (2,3)    | 6     | 11    | 0.00
 * (4,2)    | 8     | 13    | 1.62
 * (5,8)    | 40    | 27    | 0.68
 * (2,2)    | 4     | 9     | 0.00
 *
 * ===== END =====
 *
 *
 * NOTE:
 * This program will only run on POSIX-compliant OS like Linux, or other Unix-based systems. To run on Windows, you have to run it on a WSL terminal.
 *
 * HOW TO COMPILE AND RUN:
 * 1. Navigate into the same directory as this .c file.
 * 2. (Optional) While the program is running, use another terminal to print shared memory by typing:
 *    ipcs -m
 *    PLEASE NOTE: The program runs pretty quickly so if you want to check the ipcs output, provide a large number in N and then be quick to check the output of ipcs in the other terminal.
 * 3. To compile the file, enter:
 *    gcc -o prog A2_02_5.c -lpthread
 * 4. To run the file, enter:
 *    ./prog N
 *    (Where N is the input parameter mentioned above, mentioning how many (X, Y) pairs to be generated.)
 *    Example:
 *      gcc -o prog A2_02_5.c -lpthread
 *      ./prog 20
 *
 * ===== ipcs -m OUTPUT =====
 * [BEFORE PROGRAM]
 * ------ Shared Memory Segments --------
 * key        shmid      owner      perms      bytes      nattch     status
 *
 * [WHILE PROGRAM IS RUNNING]
 * ------ Shared Memory Segments --------
 * key        shmid      owner      perms      bytes      nattch     status
 * 0xffffffff 17         abish      666        2400008    1
 *
 * ===== END =====
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

#define MAX_PAIRS 100000

/* Shared memory layout */
typedef struct
{
    int X[MAX_PAIRS];
    int Y[MAX_PAIRS];
    int A[MAX_PAIRS];
    int B[MAX_PAIRS];
    double C[MAX_PAIRS];
    int N; /* number of pairs actually in use */
} shared_data;

/* Globals for shared memory */
int shmid = -1;
shared_data *shm_ptr = NULL;

/* Synchronization globals */
int current_index = 0; /* round counter: which element workers should process */
pthread_mutex_t lock;
pthread_barrier_t barrier; /* barrier count = 1 main + 3 worker threads = 4 */

/* Cleanup function for signals (Ctrl+C etc.)
   Note: can't safely destroy mutex/barrier here because
   async-signal safety is limited. Only detach & remove shm. */
void cleanup(int sig)
{
    printf("\nCaught signal %d, cleaning up shared memory...\n", sig);

    if (shm_ptr != NULL)
    {
        shmdt(shm_ptr);
        shm_ptr = NULL;
    }
    if (shmid > 0)
    {
        shmctl(shmid, IPC_RMID, NULL);
        shmid = -1;
    }
    exit(0);
}

/* Worker A: compute A[i] = X[i] * Y[i] */
void *compute_A(void *arg)
{
    while (1)
    {
        pthread_barrier_wait(&barrier); /* wait until main announces a new round */

        pthread_mutex_lock(&lock);
        int i = current_index; /* copy current round index */
        pthread_mutex_unlock(&lock);

        if (i >= shm_ptr->N)
        { /* if no more work, exit after syncing */
            pthread_barrier_wait(&barrier);
            break;
        }

        shm_ptr->A[i] = shm_ptr->X[i] * shm_ptr->Y[i];

        pthread_barrier_wait(&barrier); /* signal end of round */
    }
    return NULL;
}

/* Worker B: compute B[i] = 2*X[i] + 2*Y[i] + 1 */
void *compute_B(void *arg)
{
    while (1)
    {
        pthread_barrier_wait(&barrier);

        pthread_mutex_lock(&lock);
        int i = current_index;
        pthread_mutex_unlock(&lock);

        if (i >= shm_ptr->N)
        {
            pthread_barrier_wait(&barrier);
            break;
        }

        shm_ptr->B[i] = 2 * shm_ptr->X[i] + 2 * shm_ptr->Y[i] + 1;

        pthread_barrier_wait(&barrier);
    }
    return NULL;
}

/* Worker C: compute C[i] = B[i] / A[i] (check div by zero) */
void *compute_C(void *arg)
{
    while (1)
    {
        pthread_barrier_wait(&barrier);

        pthread_mutex_lock(&lock);
        int i = current_index;
        pthread_mutex_unlock(&lock);

        if (i >= shm_ptr->N)
        {
            pthread_barrier_wait(&barrier);
            break;
        }

        if (shm_ptr->A[i] != 0)
            shm_ptr->C[i] = (double)shm_ptr->B[i] / shm_ptr->A[i];
        else
            shm_ptr->C[i] = 0.0;

        pthread_barrier_wait(&barrier);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N < 0 || N > MAX_PAIRS)
    {
        printf("N must be between 0 and %d\n", MAX_PAIRS);
        return 1;
    }

    srand((unsigned)time(NULL));

    /* Create shared memory segment */
    key_t key = ftok("shmfile", 65);
    shmid = shmget(key, sizeof(shared_data), 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmget");
        return 1;
    }

    shm_ptr = (shared_data *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1)
    {
        perror("shmat");
        return 1;
    }

    shm_ptr->N = N;

    /* Register Ctrl+C handler */
    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    /* Fill X and Y with random numbers */
    for (int i = 0; i < N; ++i)
    {
        shm_ptr->X[i] = rand() % 10;
        shm_ptr->Y[i] = rand() % 10;
    }

    /* Init sync primitives */
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        perror("pthread_mutex_init");
        cleanup(0);
    }
    if (pthread_barrier_init(&barrier, NULL, 4) != 0)
    {
        perror("pthread_barrier_init");
        cleanup(0);
    }

    /* Launch worker threads */
    pthread_t t1, t2, t3;
    if (pthread_create(&t1, NULL, compute_A, NULL) != 0)
    {
        perror("pthread_create A");
        cleanup(0);
    }
    if (pthread_create(&t2, NULL, compute_B, NULL) != 0)
    {
        perror("pthread_create B");
        cleanup(0);
    }
    if (pthread_create(&t3, NULL, compute_C, NULL) != 0)
    {
        perror("pthread_create C");
        cleanup(0);
    }

    /* Main loop: advance one "round" per index.
       Lock ensures current_index update is atomic. */
    for (int idx = 0; idx < N; ++idx)
    {
        pthread_mutex_lock(&lock);
        current_index = idx;
        pthread_mutex_unlock(&lock);

        pthread_barrier_wait(&barrier); /* start-of-round: release workers */
        pthread_barrier_wait(&barrier); /* end-of-round: wait for workers to finish */
    }

    /* Shutdown step: tell workers there’s no more work */
    pthread_mutex_lock(&lock);
    current_index = N; /* sentinel value, tells the worker that isn't anymore work left */
    pthread_mutex_unlock(&lock);

    pthread_barrier_wait(&barrier); /* let workers check condition */
    pthread_barrier_wait(&barrier); /* sync so they can exit cleanly */

    /* Join worker threads */
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    /* Print results */
    printf("Pairs(X,Y) |   A   |   B   |    C\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < N; ++i)
    {
        printf("(%d,%d)\t | %d\t | %d\t | %.2f\n",
               shm_ptr->X[i], shm_ptr->Y[i],
               shm_ptr->A[i], shm_ptr->B[i], shm_ptr->C[i]);
    }

    /* Normal cleanup */
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    shm_ptr = NULL;
    shmid = -1;

    pthread_mutex_destroy(&lock);
    pthread_barrier_destroy(&barrier);

    return 0;
}
