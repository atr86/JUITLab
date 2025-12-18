/***********************************************************************
 *
 * 3rd Year 1st Semester OS Lab - Information Technology
 * Section: A2
 * Team Number: 02
 *    Team Member Names                   Roll Numbers
 * 1. Abishkar Chatterjee (Team Leader) - 002311001080
 * 2. Atrij Roy                         - 002311001086
 * 3. Soyeb Hoque                       - 002311001065
 *
 * Assignment: 2B (7 Marks) [CO3]
 * Description: IPC using Named Pipe (FIFO) 
 * Problem Statement: Using the fork system call, create a Child Process.. Transfer 1GB file
 * from the Parent Process to Child Process using a FIFO. Now, transfer the same file from the Child Process 
 * to the Parent Process using another FIFO. Now, compare the two files (use cmp or diff command)
 * to make sure that the same file has returned back. Also, print the time required to do this double transfer.
 * Attach this output to the source file as a comment.
 * To create FIFO, you can either use a shell command or a system call.
 * To create a large file you can use the relevant command.
 * Use ‘ls –l’ command to show the FIFO and the large file. Attach this output to the source file as a comment.
 * Make sure that the starting comment block has all the necessary information attached.
 * Input Required: None
 * Sample Output Generated:
 * =========================== OUTPUT ===========================
 * File 'original_file.bin' already exists. Skipping creation.
 * Parent: Opened 'original_file.bin' for reading.
 * Child: Opened '/tmp/fifo1' for reading.
 * Child: Opened 'returned_file.bin' for writing.
 * Parent: Opened '/tmp/fifo1' for writing.
 * Parent: Finished writing to '/tmp/fifo1'.
 * Child: Finished reading from '/tmp/fifo1'.
 * Child: Opened 'returned_file.bin' for reading.
 * Child: Opened '/tmp/fifo2' for writing.
 * Parent: Opened '/tmp/fifo2' for reading.
 * Parent: Opened 'final_file.bin' for writing.
 * Child: Finished writing to '/tmp/fifo2'.
 * Parent: Finished reading from '/tmp/fifo2'.
 * Comparing 'original_file.bin' and 'final_file.bin'...
 * Files are identical.
 * Total time for double transfer: 0.838006 seconds

 * ls -l output:
 * -rw-r--r-- 1 adminpc adminpc 1073741824 Aug  6 12:59 final_file.bin
 * -rw-r--r-- 1 adminpc adminpc 1073741824 Aug  6 12:55 original_file.bin
 * prw-rw-r-- 1 adminpc adminpc          0 Aug  6 12:59 /tmp/fifo1
 * prw-rw-r-- 1 adminpc adminpc          0 Aug  6 12:59 /tmp/fifo2

 * Cleaning up FIFO files...
 *
 * =============================================================
 *
 * NOTE: This program will only run on POSIX-compliant OS like Linux, or other Unix-based systems. 
 * To run on Windows, you have to run it on a WSL terminal. Although performance may vary on the WSL and file transfer may take longer than usual.
 *
 * How to compile and run:
 * 1. Navigate into the same directory as this .c file.
 * 2. To compile the file, enter: 
 *    gcc A2_02_2B.c
 * 3. To run the compiled file, enter:
 *    ./a.out
 *
 ************************************************************************/
#include <stdio.h> //for printf and perror command
#include <stdlib.h> //for exit(...) and system function
#include <unistd.h> //for fork, read, write methods
#include <fcntl.h> //for open, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC
#include <sys/stat.h> //for mkfifo
#include <sys/types.h> //for pid_t
#include <time.h> //for clock_gettime, struct timespec
#include <string.h> //for string operation methods
#include <sys/wait.h> //for wait process, for waiting for child processes
#include <errno.h> //for error numbers

#define FILE_SIZE (1L << 30) // 1GB
#define BUF_SIZE (64 * 1024) // 64KB
#define ORIG_FILE "original_file.bin"
#define RETURNED_FILE "returned_file.bin"
#define FINAL_FILE "final_file.bin"
#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

void create_large_file(const char *filename, size_t size) {
    struct stat st;
    if (stat(filename, &st) == 0 && st.st_size == size) { //In case file already exists we skip creation
        printf("File '%s' already exists. Skipping creation.\n", filename);
        return; 
    }

    printf("* Starting 1GB file creation...\n");
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644); //open a file for writing, and create or clear it as needed.
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    char *buffer = calloc(1, BUF_SIZE); // Zero-filled buffer
    size_t written = 0;
    while (written < size) { //writing into file to create 1 GB file
        size_t to_write = (size - written > BUF_SIZE) ? BUF_SIZE : (size - written);
        if (write(fd, buffer, to_write) != to_write) {
            perror("write");
            close(fd);
            free(buffer);
            exit(1);
        }
        written += to_write;
    }

    free(buffer);
    close(fd);
    printf("* File '%s' created successfully.\n", filename);
}

void transfer(int read_fd, int write_fd, size_t size) {
    char *buffer = malloc(BUF_SIZE);
    size_t transferred = 0; //unsigned size variable
    ssize_t n; //signed size variable (used when error can happen as it returns -1)

    while (transferred < size) {
        n = read(read_fd, buffer, BUF_SIZE);
        if (n <= 0) break;
        write(write_fd, buffer, n);
        transferred += n;
    }

    free(buffer);
}

int main() {
    struct timespec start, end;
    unlink(RETURNED_FILE); //deleting previously created files to improve performance
    unlink(FINAL_FILE);
    unlink(FIFO1);
    unlink(FIFO2);
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    create_large_file(ORIG_FILE, FILE_SIZE); 

    clock_gettime(CLOCK_MONOTONIC, &start); //track the starting time with the clock_gettime function and store it in start struct

    pid_t pid = fork(); //Creating two threads
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        int fifo_read = open(FIFO1, O_RDONLY);
        printf("* Child: Opened '%s' for reading.\n", FIFO1);

        int out_fd = open(RETURNED_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        printf("* Child: Opened '%s' for writing.\n", RETURNED_FILE);

        transfer(fifo_read, out_fd, FILE_SIZE);
        printf("* Child: Finished reading from '%s'.\n", FIFO1);

        close(fifo_read);
        close(out_fd);

        // Now send the file back
        int in_fd = open(RETURNED_FILE, O_RDONLY);
        printf("* Child: Opened '%s' for reading.\n", RETURNED_FILE);

        int fifo_write = open(FIFO2, O_WRONLY);
        printf("* Child: Opened '%s' for writing.\n", FIFO2);

        transfer(in_fd, fifo_write, FILE_SIZE);
        printf("* Child: Finished writing to '%s'.\n", FIFO2);

        close(in_fd);
        close(fifo_write);

        exit(0);
    } else {
        // Parent process
        int in_fd = open(ORIG_FILE, O_RDONLY);
        printf("* Parent: Opened '%s' for reading.\n", ORIG_FILE);

        int fifo_write = open(FIFO1, O_WRONLY);
        printf("* Parent: Opened '%s' for writing.\n", FIFO1);

        transfer(in_fd, fifo_write, FILE_SIZE);
        printf("* Parent: Finished writing to '%s'.\n", FIFO1);

        close(in_fd);
        close(fifo_write);

        // Receive back
        int fifo_read = open(FIFO2, O_RDONLY);
        printf("* Parent: Opened '%s' for reading.\n", FIFO2);

        int out_fd = open(FINAL_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        printf("* Parent: Opened '%s' for writing.\n", FINAL_FILE);

        transfer(fifo_read, out_fd, FILE_SIZE);
        printf("* Parent: Finished reading from '%s'.\n", FIFO2);

        close(fifo_read);
        close(out_fd);

        wait(NULL);
        clock_gettime(CLOCK_MONOTONIC, &end); //track the ending time with the clock_gettime function and store it in end struct

        // Compare files
        printf("* Comparing '%s' and '%s'...\n", ORIG_FILE, FINAL_FILE);
        int cmp_result = system("cmp -s original_file.bin final_file.bin"); //checking if the two files are identical
        if (cmp_result == 0) {
            printf("* Files are identical.\n");
        } else {
            printf("* Files differ.\n");
        }

        double time_taken = (end.tv_sec - start.tv_sec) + 
                            (end.tv_nsec - start.tv_nsec) / 1e9; //Calculate the total time taken
        printf("* Total time for double transfer: %.6f seconds\n", time_taken);

        // ls -l output
        printf("\n* ls -l output:\n");
        system("ls -l original_file.bin final_file.bin /tmp/fifo1 /tmp/fifo2");

        // Cleanup
        printf("\n Cleaning up FIFO files...\n");
        unlink(FIFO1);
        unlink(FIFO2);
    }

    return 0;
}




