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
 * Assignment: 1B (4 Marks) [CO1]
 * Description: Program to get and set environment variables using system calls
 * Problem Statement: Program to GET and SET the Environment variable and to know the use of getenv and setenv system calls
 * Input Required: None
 * Sample Output Generated:
 * === Default Environment Variables ===
 *  USER = user
 *  HOME = /home/user
 *  HOST is not set in the environment.
 *  ARCH is not set in the environment.
 *  DISPLAY = :0
 *  PRINTER is not set in the environment.
 *  PATH = /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
 *
 *  === Setting Custom Environment Variables ===
 *  MY_VAR1 = Environment_Test
 *  MY_VAR2 = 12345
 *
 * NOTE: This program will only run on POSIX-compliant OS like Linux, or other Unix-based systems. 
 * To run on Windows, you have to run it on a WSL terminal. Otherwise, it does not recognise the 'setenv()' function.
 * 
 * How to compile and run:
 * 1. Navigate into the same directory as this .c file.
 * 2. To compile the file, enter: 
 *    gcc A2_02_1B.c
 * 3. To run the compiled file, enter:
 *    ./a.out
 * 
 * 
 ***********************************************************************/


 
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // List of environment variable names to retrieve
    const char *variables[] = {
        "USER",
        "HOME",
        "HOST",
        "ARCH",
        "DISPLAY",
        "PRINTER",
        "PATH"};
    int num_vars = 7; // No of elements in the above array

    printf("=== Default Environment Variables ===\n");
    for (int i = 0; i < num_vars; ++i)
    {
        const char *value = getenv(variables[i]);
        if (value) //If the value exists
            printf("%s = %s\n", variables[i], value);
        else
            printf("%s is not set in the environment.\n", variables[i]);
    }

    // Setting custom environment variables
    printf("\n=== Setting Custom Environment Variables ===\n");
    if (setenv("MY_VAR1", "Environment_Test", 1) != 0)
    {
        perror("Failed to set MY_VAR1"); //In case we are unable to set custom variables
    }

    if (setenv("MY_VAR2", "12345", 1) != 0)
    {
        perror("Failed to set MY_VAR2");
    }

    // Display the custom environment variables
    printf("MY_VAR1 = %s\n", getenv("MY_VAR1"));
    printf("MY_VAR2 = %s\n", getenv("MY_VAR2"));

    return 0;
}
