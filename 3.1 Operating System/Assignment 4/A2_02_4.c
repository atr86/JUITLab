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
 * Assignment: 4 (10 Marks) [CO2]
 * Description: The objective of this programming assignment is to use mmap() call and observe page-fault using the ‘sar’ command.
 * A big file (about 8GB) should be created using the ‘fallocate’ command. This big file should be written with a single byte value (say X) at a specific
 * offset (say F). Both the values and the offset should be generated using a random function. Please do remember this random function should
 * generate a quantity anywhere between 0 and 8G for the value of F and between 0-255 for the value of X.
 * The above big file should also be mapped in the virtual address space using mmap() call. Once it is mapped, the data should be read from the
 * same specific offset (F). Now, if the data read is X`; then verify that X and X` are the same. In case of verification failure, an error message is to be
 * printed and also the program should terminate. Note that, the offset value F can be anywhere between 0 and 8G and you should display the offset as
 * hex number format.
 * This sequence of writing and reading data to/from a specific offset and also verification should be put in a while loop to go forever.
 * In another terminal execute the command ‘sar –B 1’ to observe for the page fault. This command should be started before the above program is
 * put under execution. So, one can observe that the page faults are increasing, once the above program starts executing.
 * The output of the program and the ‘sar’ command should be pasted as a comment at the beginning of the program file as indicated by the
 * guidelines.
 *
 * Input Required: An 8GB text file, for example: bigfile.txt. You have to create the 8GB file with the command: fallocate -l 8G bigfile.txt
 *
 * Sample Output Generated:
 * === Running program ===
 * adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/un$ fallocate -l 8G bigfile.txt
 * adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/un$ gcc A2_02_4.c -o a
 * adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/un$ ./a bigfile.txt
 * === Output of Code ===
 * Verified at offset 0x123494f04: Written value = 127 (0x7F), Read value = 127 (0x7F)
 * Verified at offset 0xd263c9e3: Written value = 171 (0xAB), Read value = 171 (0xAB)
 * Verified at offset 0x1cee58357: Written value = 31 (0x1F), Read value = 31 (0x1F)
 * Verified at offset 0x13f169309: Written value = 99 (0x63), Read value = 99 (0x63)
 * Verified at offset 0x67b112b4: Written value = 160 (0xA0), Read value = 160 (0xA0)
 * Verified at offset 0x162b56158: Written value = 3 (0x03), Read value = 3 (0x03)
 * Verified at offset 0x1a79b909e: Written value = 173 (0xAD), Read value = 173 (0xAD)
 * Verified at offset 0x101d906c4: Written value = 56 (0x38), Read value = 56 (0x38)
 * Verified at offset 0x8a6d431: Written value = 92 (0x5C), Read value = 92 (0x5C)
 * Verified at offset 0x107d3f7c9: Written value = 160 (0xA0), Read value = 160 (0xA0)
 * Verified at offset 0xa0a25437: Written value = 164 (0xA4), Read value = 164 (0xA4)
 * Verified at offset 0x3c07df5c: Written value = 136 (0x88), Read value = 136 (0x88)
 * Verified at offset 0x1af29bdb3: Written value = 223 (0xDF), Read value = 223 (0xDF)
 * Verified at offset 0x1dbf0376e: Written value = 232 (0xE8), Read value = 232 (0xE8)
 * Verified at offset 0x168785af6: Written value = 156 (0x9C), Read value = 156 (0x9C)
 * Verified at offset 0x179ac4c78: Written value = 244 (0xF4), Read value = 244 (0xF4)
 * Verified at offset 0xb25a248c: Written value = 147 (0x93), Read value = 147 (0x93)
 * Verified at offset 0x115221e66: Written value = 87 (0x57), Read value = 87 (0x57)
 * Verified at offset 0x17cd4a8d6: Written value = 137 (0x89), Read value = 137 (0x89)
 * Verified at offset 0x155e278f1: Written value = 82 (0x52), Read value = 82 (0x52)
 * Verified at offset 0x10d5ed4f6: Written value = 137 (0x89), Read value = 137 (0x89)
 * Verified at offset 0x1c782197a: Written value = 230 (0xE6), Read value = 230 (0xE6)
 * Verified at offset 0x1e98db9aa: Written value = 153 (0x99), Read value = 153 (0x99)
 * Verified at offset 0x126b816f9: Written value = 7 (0x07), Read value = 7 (0x07)
 * Verified at offset 0x15d633cab: Written value = 254 (0xFE), Read value = 254 (0xFE)
 * Verified at offset 0x13779e1fd: Written value = 118 (0x76), Read value = 118 (0x76)
 * Verified at offset 0x11d89c553: Written value = 2 (0x02), Read value = 2 (0x02)
 * Verified at offset 0xf1b98a55: Written value = 104 (0x68), Read value = 104 (0x68)
 * Verified at offset 0xc0eea990: Written value = 63 (0x3F), Read value = 63 (0x3F)
 * Verified at offset 0x11686b326: Written value = 48 (0x30), Read value = 48 (0x30)
 * Verified at offset 0x65ca6c5d: Written value = 38 (0x26), Read value = 38 (0x26)
 * ^C
 * === End ===
 *
 * NOTE: This program will only run on POSIX-compliant OS like Linux, or other Unix-based systems.
 * Try not to run it on WSL as it will take a LONG time.
 *
 * Compile and Run Instructions:
 * 1. Optional: To observe page faults, open up another terminal in the very beginning before running the program and run this:
 *      sar -B 1
 * 2. Navigate into the directory. Before compiling, to create the 8GB file and store it to the disk, run this command:
 *      fallocate -l 8G bigfile.txt
 * 3. To compile the file, enter:
 *      gcc file.c -o file
 * 4. To run the compiled file, use the name you gave the big file and run this command:
 *      ./file bigfile.txt
 *    
 * Note how in the output of sar given below the page fault increases while program is running and then becomes normal after the main program is interrupted by Ctrl C.
 * 
 * === Output of sar in the 2nd terminal ===
 * (Running sar before starting the source code execution and interrupting sar only after interrupting main program)
 * 
 * adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/un$ sar -B 1
 * Linux 5.15.0-139-generic (adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC) 	20/08/25 	_x86_64_	(12 CPU)
 *
 * 01:38:01 PM IST  pgpgin/s pgpgout/s   fault/s  majflt/s  pgfree/s pgscank/s pgscand/s pgsteal/s	%vmeff
 * 01:38:02 PM IST  	0.00  	0.00 	 14.00  	0.00 	 53.00   	0.00  	0.00  	0.00  	0.00
 * 01:38:03 PM IST  	0.00  	0.00  	3.00  	0.00	159.00  	            0.00  	0.00  	0.00  	0.00
 * 01:38:04 PM IST  	0.00  	8.00	519.00  0.00	790.00  		0.00  	0.00  	0.00  	0.00
 * 01:38:05 PM IST  	0.00   7528.00 11.00  	0.00	272.00  		0.00  	0.00  	0.00  	0.00
 * 01:38:06 PM IST  	0.00 	32.00 	92.00  	0.00	393.00  		0.00  	0.00  	0.00  	0.00
 * 01:38:07 PM IST  	0.00  	0.00   4239.00  	0.00   2825.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:08 PM IST  	0.00	160.00 150443.00  	0.00   1247.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:09 PM IST  	0.00	204.00 136534.00  	0.00   2806.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:10 PM IST  	0.00 524108.00 113181.00  	0.00   3544.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:11 PM IST  	0.00 1093192.00 100791.00  	0.00   6232.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:12 PM IST  	0.00 559340.00  99463.00  	0.00   5220.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:13 PM IST  	0.00 178228.00  96169.00  	0.00   4576.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:14 PM IST  	0.00 566452.00  82904.00  	0.00   5289.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:15 PM IST  	0.00 645436.00  83206.00  	0.00   6340.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:16 PM IST  	0.00 940796.00  73129.00  	0.00   9436.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:17 PM IST  	0.00 780608.00  66601.00  	0.00   9740.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:18 PM IST  	0.00 262336.00  69511.00  	0.00   3327.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:19 PM IST  	0.00 535492.00  60192.00  	0.00   6697.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:20 PM IST  	0.00 524808.00  49804.00  	0.00   5924.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:21 PM IST  	0.00 893112.00  52505.00  	0.00  10024.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:22 PM IST  	0.00 952468.00  45934.00  	0.00  12696.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:23 PM IST  	0.00  76348.00   118.00  	0.00   7117.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:24 PM IST  	0.00  	0.00 	    27.00  	0.00	185.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:25 PM IST  	0.00  	0.00 	    56.00  	0.00   2152.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:26 PM IST  	0.00  	0.00  	    1.00  	0.00	222.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:27 PM IST  	0.00  27660.00    8.00  	0.00	325.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:28 PM IST  	0.00 535868.00   64.00  	0.00   5957.00  	0.00  	0.00  	0.00  	0.00
 * 01:38:29 PM IST  	0.00 126056.00   35.00  	0.00   2264.00  	0.00  	0.00  	0.00  	0.00
 * ^C
 * 
 * Average:     	0.00 329651.43  45912.64  	0.00   4136.14  	0.00  	0.00  	0.00  	0.00
 * adminpc@adminpc-HP-Pro-Tower-280-G9-PCI-Desktop-PC:~/un$
 * === End ===
 *
 ************************************************************************/


#define _XOPEN_SOURCE 701   // Enable POSIX extensions (for mmap, random, etc.)

#include <stdio.h>     
#include <stdlib.h>     // random, srand, exit
#include <time.h>       // time (for seeding RNG)
#include <fcntl.h>      // open, O_RDWR
#include <unistd.h>     // pwrite, close
#include <sys/mman.h>   // mmap, munmap
#include <sys/stat.h>   // struct stat

// Define the file size as 8 GB
#define FILE_SIZE (8LL * 1024 * 1024 * 1024) //LL stands for long long

int main(int argc, char *argv[]) 
{
    // Require filename as argument
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1]; //extract file name - bigfile.txt

    // 1. Open file in read/write mode
    int fd = open(filename, O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 2. Map the file into memory (entire 8GB space)
    unsigned char *map = mmap(NULL, FILE_SIZE,
                              PROT_READ | PROT_WRITE,  // allow read/write
                              MAP_SHARED,              // changes sync to file
                              fd, 0);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    // 3. Seed the random number generator - use present time so it is most random
    srand(time(NULL));

    // 4. Infinite loop
    while (1) {


        // Generate a random offset (0 … 8GB-1).
        // Use two calls to random()(each gives a 31 bit number) combined into a 62-bit number,
        // then mod by FILE_SIZE to fit inside the 8GB range.


        off_t F = ((unsigned long long)random() << 31 | random()) % FILE_SIZE;

        // Generate a random byte value (0–255)
        unsigned char X = random() % 256;

        // Write the value directly to the file at offset F
        if (pwrite(fd, &X, 1, F) != 1) {
            perror("pwrite");
            break;
        }

        // Read the value back from the mapped region at same offset
        unsigned char Xdash = map[F];

        // Verify written and read values match or not
        if (X != Xdash) {// if does not get matched
            fprintf(stderr,
                "Verification failed at offset 0x%llx: wrote %u (0x%02X) but read %u (0x%02X)\n",
                (unsigned long long)F, X, X, Xdash, Xdash);// %u prints no. & 0x%02X in hex
            break;
        } else {//if get matched
            printf("Verified at offset 0x%llx: Written value = %u (0x%02X), Read value = %u (0x%02X)\n",
            (unsigned long long)F, X, X, Xdash, Xdash);
        }


    }

    // 5. Cleanup: unmap memory and close file --
    munmap(map, FILE_SIZE);// munmap to unmap memory
    close(fd);
    return 0;
}

