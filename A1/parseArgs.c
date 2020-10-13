/*
 * Author: Chris Dorr & Jordyn Marlow
 * Assignment Number: 1
 * Date of Submission: 10/DD/2020
 * parseArgs.c
 *
 * Preliminary pass at parsing of options and their arguments 
 * using getopt().
 * To be further adapted to Assignment
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int GETOPT_FAILURE = -1;

int main(int argc, char *argv[]) {
    int op;
    int pid;
    bool pid_was_set = false;

    while ((op = getopt(argc, argv, "p:stvc")) != GETOPT_FAILURE) {
        switch (op) {
	    case 'p':
		//Display PID when given PID value as argument
 		pid = atoi(optarg);
		pid_was_set = true;
	        break;
            case 's':
		//Single Character State Information
		break;
            case 't':
		//utime information
	        break;
            case 'v':
		//Virtual Memory Used (Pages)
	        break;
            case 'c':
		//Display Command Line which started this process
                break;
	    default:
                printf("No recognized arguments\n");
		exit(EXIT_FAILURE);
	}	
    }
    if (pid_was_set) {
        printf("PID: %i\n", pid);
    }
    exit(EXIT_SUCCESS);
}
