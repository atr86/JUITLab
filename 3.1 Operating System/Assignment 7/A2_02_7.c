/*
 * avoid_deadlock.c
 *
 * Assignment: avoid deadlock while manipulating three shared totals.
 *
 * Globals:
 *   Total_1, Total_2, Total_3  -- initialized to 100000 each
 *   mutex1, mutex2, mutex3     -- protect each Total
 *
 * Threads:
 *   Th1: generate random qty <= 10, subtract from Total_1, add to either Total_2 or Total_3
 *   Th2: generate random qty <= 20, subtract from Total_2, add to either Total_1 or Total_3
 *   Th3: generate random qty <= 30, subtract from Total_3, add to either Total_1 or Total_2
 *   Th4: periodically print Total_1, Total_2, Total_3 and grand total
 *
 * Program runs forever.
 *==========================================================
 * Deadlock reasoning / ordering:
 * ------------------------------
 * Deadlock arises when two threads lock mutexes in conflicting orders:
 *   e.g., Thread A locks mutex1 then mutex2, Thread B locks mutex2 then mutex1.
 *   If A locks mutex1 and B locks mutex2, each waits for the other -> deadlock.
 *
 * To avoid deadlock, this program uses a single canonical ordering of mutex acquisition:
 *   always lock mutexes according to their index order: mutex1 < mutex2 < mutex3.
 * For any operation that needs multiple locks, we:
 *   - compute the ordering of the needed mutex indices,
 *   - lock them in increasing order,
 *   - perform updates,
 *   - unlock them in reverse order (unlocking order does not reintroduce deadlock, but done in reverse for similarity and readability).
 *
 * This consistent ordering guarantees that no cyclic wait can occur, so deadlock is avoided.
 *===============================================================================
 * Deadlock can occur if threads acquire multiple mutexes in different orders.
 * For example, if Th1 locks mutex1 then mutex2, and Th2 locks mutex2 then mutex1,
 * both threads may wait forever for the other to release a mutex (circular wait).
 * To prevent this, all threads in this program lock mutexes in a consistent
 * global order (mutex1 → mutex2 → mutex3), avoiding deadlock. 
 *============================================================================================
 * Threads are deliberately paused using nanosleep to simulate realistic
 * processing delays and allow other threads to run, making the
 * output interleaving visible and preventing CPU from being fully pegged. 


 * Compile:
 *   gcc avoid_deadlock.c -o avoid_deadlock -lpthread
 *
 * Run:
 *   ./avoid_deadlock
  
aroy@aroy-VirtualBox:~/Documents/oslab$ gcc A2_02_7.c -lpthread -o prog
aroy@aroy-VirtualBox:~/Documents/oslab$ ./prog
[Th1] moved 9 from Total_1 -> Total_3 | 
[Th3] moved 13 from Total_3 -> Total_2 | 
[Th2] moved 6 from Total_2 -> Total_1 |
=== [Th4] Snapshot => T1=99997  T2=100007  T3=99996  Grand=300000 ===
[Th3] moved 17 from Total_3 -> Total_2 | 
=== [Th4] Snapshot => T1=99997  T2=100024  T3=99979  Grand=300000 ===
[Th1] moved 7 from Total_1 -> Total_2 | 
[Th2] moved 10 from Total_2 -> Total_3 |
[Th3] moved 4 from Total_3 -> Total_1 | 
[Th3] moved 6 from Total_3 -> Total_1 | 
[Th2] moved 19 from Total_2 -> Total_3 |
=== [Th4] Snapshot => T1=100000  T2=100002  T3=99998  Grand=300000 ===
[Th1] moved 1 from Total_1 -> Total_3 | 
[Th3] moved 3 from Total_3 -> Total_2 | 
[Th2] moved 3 from Total_2 -> Total_3 |
[Th3] moved 10 from Total_3 -> Total_1 | 
[Th2] moved 6 from Total_2 -> Total_1 |
=== [Th4] Snapshot => T1=100015  T2=99996  T3=99989  Grand=300000 ===
[Th3] moved 6 from Total_3 -> Total_1 | 
[Th1] moved 3 from Total_1 -> Total_3 | 
=== [Th4] Snapshot => T1=100018  T2=99996  T3=99986  Grand=300000 ===
[Th2] moved 4 from Total_2 -> Total_3 |
[Th3] moved 24 from Total_3 -> Total_2 | 
[Th1] moved 3 from Total_1 -> Total_2 | 
[Th3] moved 17 from Total_3 -> Total_1 | 
=== [Th4] Snapshot => T1=100032  T2=100019  T3=99949  Grand=300000 ===
[Th1] moved 5 from Total_1 -> Total_3 | 
[Th2] moved 5 from Total_2 -> Total_1 |
[Th3] moved 4 from Total_3 -> Total_1 | 
[Th3] moved 22 from Total_3 -> Total_2 | 
=== [Th4] Snapshot => T1=100036  T2=100036  T3=99928  Grand=300000 ===
[Th2] moved 2 from Total_2 -> Total_3 |
[Th1] moved 4 from Total_1 -> Total_2 | 
[Th2] moved 8 from Total_2 -> Total_3 |
[Th3] moved 6 from Total_3 -> Total_2 | 
[Th1] moved 7 from Total_1 -> Total_3 | 
[Th3] moved 19 from Total_3 -> Total_2 | 
=== [Th4] Snapshot => T1=100025  T2=100055  T3=99920  Grand=300000 ===
[Th2] moved 7 from Total_2 -> Total_1 |


 *
 */
#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>     // usleep
#include <time.h>       // time

/* Shared totals */
long long Total_1 = 100000;
long long Total_2 = 100000;
long long Total_3 = 100000;

/* Mutexes for each total */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

/* Helper: lock two mutexes in canonical order (by index) */
void lock_two(int a, int b) {
    // a and b are in {1,2,3}
    if (a == b)
    	 return;
    if (a > b) 
    { 
    	int tmp = a;
     	a = b;
      	b = tmp; 
    }//make a<b to maintain ascending order in obtaining locks

    if (a == 1) pthread_mutex_lock(&mutex1);
    else if (a == 2) pthread_mutex_lock(&mutex2);
    else pthread_mutex_lock(&mutex3);

    if (b == 1) pthread_mutex_lock(&mutex1);
    else if (b == 2) pthread_mutex_lock(&mutex2);
    else pthread_mutex_lock(&mutex3);
}

/* Unlock two mutexes (order not important, but we'll unlock in reverse, to maintain symmetry and readibility) */
void unlock_two(int a, int b) {
    if (a == b) return;
    if (a > b) { int tmp = a; a = b; b = tmp; }

    // unlock b then a (reverse of lock order)
    if (b == 1) pthread_mutex_unlock(&mutex1);
    else if (b == 2) pthread_mutex_unlock(&mutex2);
    else pthread_mutex_unlock(&mutex3);

    if (a == 1) pthread_mutex_unlock(&mutex1);
    else if (a == 2) pthread_mutex_unlock(&mutex2);
    else pthread_mutex_unlock(&mutex3);
}

/* Lock all three mutexes in canonical order */
void lock_all_three() {
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);
    pthread_mutex_lock(&mutex3);
}

/* Unlock all three (reverse order) */
void unlock_all_three() {
    pthread_mutex_unlock(&mutex3);
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
}

/* Thread functions */

/* Th1: move random qty (<=10) from Total_1 to [ Total_2 or Total_3] */
void *Th1(void *arg) 
{
    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)pthread_self();
    // Each thread uses its own seed for rand_r() to generate independent
    // random numbers and avoid contention on the global rand() state.

    while (1) {
        int qty = (rand_r(&seed) % 10) + 1; // 1..10
        int dest = (rand_r(&seed) % 2) ? 2 : 3;

        // lock Total_1 and destination in canonical order to avoid deadlock
        lock_two(1, dest);

        // Check and perform
        if (Total_1 >= qty) {
            Total_1 -= qty;
            if (dest == 2) Total_2 += qty;
            else Total_3 += qty;

            printf("[Th1] moved %d from Total_1 -> Total_%d | \n",
                   qty, dest);//T1=%lld T2=%lld T3=%lld
        } else {
            // Not enough in Total_1 — just print
            printf("[Th1] wanted %d from Total_1 but insufficient (T1=%lld). Skipping.\n",
                   qty, Total_1);
        }

        unlock_two(1, dest);

        struct timespec ts;
ts.tv_sec = 0;
ts.tv_nsec = (10000 + (rand_r(&seed) % 20000)) * 1000L; // convert µs → ns
nanosleep(&ts, NULL);
 // sleep 10-30 ms
    }
    return NULL;
}

/* Th2: move random qty (<=20) from Total_2 to [Total_1 or Total_3] */
void *Th2(void *arg) {
    unsigned int seed = (unsigned int)time(NULL) ^ ((unsigned int)pthread_self() << 1);
    // Each thread uses its own seed for rand_r() to generate independent
    // random numbers and avoid contention on the global rand() state.

    while (1) {
        int qty = (rand_r(&seed) % 20) + 1; // 1..20
        int dest = (rand_r(&seed) % 2) ? 1 : 3;

        // lock Total_2 and destination in canonical order
        lock_two(2, dest);

        if (Total_2 >= qty) {
            Total_2 -= qty;
            if (dest == 1) Total_1 += qty;
            else Total_3 += qty;

            printf("[Th2] moved %d from Total_2 -> Total_%d |\n",
                   qty, dest);//T1=%lld T2=%lld T3=%lld
        } else {
            printf("[Th2] wanted %d from Total_2 but insufficient (T2=%lld). Skipping.\n",
                   qty, Total_2);
        }

        unlock_two(2, dest);

        struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = (10000 + (rand_r(&seed) % 20000)) * 1000L; // convert µs → ns
	nanosleep(&ts, NULL);
 	// sleep 10-30 ms
    }
    return NULL;
}

/* Th3: move random qty (<=30) from Total_3 to [Total_1 or Total_2] */
void *Th3(void *arg) {
    unsigned int seed = (unsigned int)time(NULL) ^ ((unsigned int)pthread_self() << 2);
    // Each thread uses its own seed for rand_r() to generate independent
    // random numbers and avoid contention on the global rand() state.

    while (1) 
    {
        int qty = (rand_r(&seed) % 30) + 1; // 1..30
        int dest = (rand_r(&seed) % 2) ? 1 : 2;

        // lock Total_3 and destination in canonical order
        lock_two(3, dest);

        if (Total_3 >= qty) {
            Total_3 -= qty;
            if (dest == 1) Total_1 += qty;
            else Total_2 += qty;

            printf("[Th3] moved %d from Total_3 -> Total_%d | \n",
                   qty, dest);//T1=%lld T2=%lld T3=%lld
        } else {
            printf("[Th3] wanted %d from Total_3 but insufficient (T3=%lld). Skipping.\n",
                   qty, Total_3);
        }

        unlock_two(3, dest);

        struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = (10000 + (rand_r(&seed) % 20000)) * 1000L; // convert µs → ns
	nanosleep(&ts, NULL);
 // sleep 10-30 ms
    }
    return NULL;
}

/* Th4: display totals and grand total consistently */
void *Th4(void *arg) {
    (void)arg;
    unsigned int seed = (unsigned int)time(NULL) ^ ((unsigned int)pthread_self() << 2);
    while (1) {
        // Acquire all three locks in canonical order to create a consistent snapshot
        lock_all_three();
        long long t1 = Total_1;
        long long t2 = Total_2;
        long long t3 = Total_3;
        long long grand = t1 + t2 + t3;

        printf("=== [Th4] Snapshot => T1=%lld  T2=%lld  T3=%lld  Grand=%lld ===\n",
               t1, t2, t3, grand);

        unlock_all_three();
	struct timespec ts;
ts.tv_sec = 0;
ts.tv_nsec = (10000 + (rand_r(&seed) % 20000)) * 1000L; // convert µs → ns
nanosleep(&ts, NULL);
 // sleep 10-30 ms
        // Show snapshots less frequently
        //usleep(100000); // 100 ms
    }
    return NULL;
}

int main() {
    pthread_t th1, th2, th3, th4;

    // Seed global RNG for some variety (threads use rand_r anyway)
    srand((unsigned int)time(NULL));

    if (pthread_create(&th1, NULL, Th1, NULL) != 0) {
        perror("pthread_create Th1");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&th2, NULL, Th2, NULL) != 0) {
        perror("pthread_create Th2");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&th3, NULL, Th3, NULL) != 0) {
        perror("pthread_create Th3");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&th4, NULL, Th4, NULL) != 0) {
        perror("pthread_create Th4");
        exit(EXIT_FAILURE);
    }

    // Let threads run forever; join them (they never exit)
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);

    return 0;
}

