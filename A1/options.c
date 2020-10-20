/*
 * Authors: Christopher Dorr & Jordyn Marlow
 * Assignment Number: 1
 * Date of Submission: 10/21/20
 *
 * options.c
 */
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#include "options.h"

char return_state_character(int pid) {
    // -s
    char stat_proc_string[100];
    sprintf(stat_proc_string, "/proc/%d/stat", pid);
    
    DIR* stat = opendir(stat_proc_string);
    if (stat != NULL)
    {
        // entry = readdir(stat);
        // parse stat for single-character state
        return 'k';
    }
}
   
char* return_uptime(int pid) { 
// -t

    char stat_proc_string[100];
    sprintf(stat_proc_string, "/proc/%d/stat", pid);
    DIR* stat = opendir(stat_proc_string);
    if (stat != NULL)
    {
        // add utime to stime and display in hh:mm:ss
    }
}
 
/*
 * Function: assign_virtual_mem
 *
 * Input:
 *     pid: Process ID given by the user, or 1 if not provided
 *     ret: Pointer to string defined in main. Output string 
 *          written here.
 *
 * Output:
 *     No output. Result is written to pre-allocated memory.
 *
 * Description: Gathers size in pages of virtual memory being
 *              used by process described by given process ID
 *              (or PID = 1, if no user provided PID)
 */

void assign_virtual_mem(int pid, char* ret) {
    	
    /* Open directory we are looking for the given PID in, /proc */	
    DIR* proc = opendir(PROC_PATH);
    struct dirent* entry;

    /* Loop over directories in /proc, when we find a directory name
     * which matches the given PID, proceed with parsing */
    while (entry = readdir(proc)) {
	if (strtol (entry -> d_name, NULL, 10) == pid) {

	    /* Declare a general buffer for parsing, and a buffer 
	     * to store the path to the PID's statm file */
	    char buffer[BUFFER_LEN];
            char statm_path[BUFFER_LEN];

            sprintf(statm_path, "/proc/%d/statm", pid); //Store path in buffer
           
	    /* Open statm file and get a reasonable amount of it.
	     * We should not need the whole file, as the virtual memory
	     * is the first piece of data stored in the file. */
	    FILE* statm = fopen(statm_path, "r");
	    fgets(buffer, FILE_GET_SIZE, statm);    

	    /* Store string in preallocated memory and close statm */ 
	    strcpy(ret, strtok(buffer, " "));
	    fclose(statm);
	}
    }
}

/*
 * Function: assign_command_line
 *
 * Input:
 *     pid: Process ID given by the user, or 1 if not provided
 *     ret: Pointer to string defined in main. Output string 
 *          written here.
 *
 * Output:
 *     No output. Result is written to pre-allocated memory.
 *
 * Description: Gathers string used on the command line to start the
 *              process described by given process ID
 *              (or PID = 1, if no user provided PID)
 */

void assign_command_line(int pid, char* ret) {


    /* Open directory we are looking for the given PID in, /proc */	
    DIR* proc = opendir(PROC_PATH);
    struct dirent* entry;

    
    /* Loop over directories in /proc, when we find a directory name
     * which matches the given PID, proceed with parsing */
    while (entry = readdir(proc)) {
        if (strtol(entry -> d_name, NULL, 10) == pid) {

	    /* Declare a buffer for storing the cmdline file's path */
	    char cmdline_path[BUFFER_LEN];
            sprintf(cmdline_path, "/proc/%d/cmdline", pid); //Store path

	    /* Open cmdline file and store data in preallocated buffer. 
	     * Close cmdline */
	    FILE* cmdline = fopen(cmdline_path, "r");
	    fgets(ret, FILE_GET_SIZE, cmdline);
	    fclose(cmdline);
	}
    }
}
