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
#include "options.h"

const int GETOPT_FAILURE = -1;

int main(int argc, char *argv[]) {
    int op;
    int pid;
    bool pid_was_set = false;


    char state_char;
    char* uptime;
    char* virtual_mem;
    char* cmd_line;

    while ((op = getopt(argc, argv, "p:stvc")) != GETOPT_FAILURE) {
        switch (op) {
	    case 'p':
		//Display PID when given PID value as argument
 		pid = atoi(optarg);
		pid_was_set = true;
	        break;
            case 's':
	        //Single Character State Information
                state_char = return_state_character(pid);
		break;
            case 't':
	        //utime information
		uptime = return_uptime(pid);
	        break;
            case 'v':
		//Virtual Memory Used (Pages)
		virtual_mem = return_virtual_mem(pid);
	        break;
            case 'c':
		//Display Command Line which started this process
                cmd_line = return_command_line(pid);
		break;

        }
    }
    if (pid_was_set) {
        printf("PID: %i\n", pid);
    }
    exit(EXIT_SUCCESS);
}
