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
 * Assignment: 2A (3 Marks) [CO3]
 * Description: Catch the signal ‘SIGINT’ and display “Ha Ha, Not Stopping”. Use  ‘signal’ system call. 
 * Warning: Always use “perror” to check the return status of a library/system call.
 * Input Required: None
 * Sample Output Generated:
 * === Output ===
 * Time: 2025-08-06 13:16:55. Running Process Id:5712. 
 * Time: 2025-08-06 13:16:56. Running Process Id:5712. 
 * Time: 2025-08-06 13:16:57. Running Process Id:5712. 
 * ^C
 * Ha Ha Not Stopping
 *
 * Press CTRL + Z to exit 
 *
 * Time: 2025-08-06 13:16:57. Running Process Id:5712. 
 * Time: 2025-08-06 13:16:58. Running Process Id:5712. 
 * Time: 2025-08-06 13:16:59. Running Process Id:5712. 
 * ^Z
 * [2]+  Stopped                 ./a.out
 * === End ===
 *
 * NOTE: This program will only run on POSIX-compliant OS like Linux, or other Unix-based systems. 
 * To run on Windows, you have to run it on a WSL terminal.
 *
 * How to compile and run:
 * 1. Navigate into the same directory as this .c file.
 * 2. To compile the file, enter: 
 *    gcc A2_02_2A.c
 * 3. To run the compiled file, enter:
 *    ./a.out
 * 4. NOTE: You cannot stop the program with CTRL + C, use CTRL + Z instead.
 *
 ************************************************************************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void signal_handler()
{
    write(STDOUT_FILENO,"\n\nHa Ha Not Stopping\n\n",23);//write(where, "", string length)
    write(STDOUT_FILENO,"Press CTRL + Z to exit \n\n",26);//Alt exit option
}


int main()
{

    if(signal(SIGINT, signal_handler)==SIG_ERR)//Pressing CTRL+C returns an interrupt which is in form of SIGINT
    {
        perror("Something went wrong"); //SIG_ERR means something went wrong and didn't work as intended.
        exit(1); //Exits the program with an error
    }

    while(1)
    {    
        time_t now=time(NULL); //a long integer used to store time in seconds since the Unix Epoch (00:00:00 UTC in January 1, 1970)
        struct tm *local=localtime(&now); //Converts the time to local time pointing to a struct
        char buffer[80];
        strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S", local); 
        printf("Time: %s. Running Process Id:%d. \n",buffer, getpid()); //Prints the time infinitely until interrupted
        sleep(1); //Makes it so that time printing is done each second.
    }
    return 0;
}

