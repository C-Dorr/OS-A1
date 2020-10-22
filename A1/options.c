/*
 * Authors: Christopher Dorr & Jordyn Marlow
 * Assignment Number: 1
 * Date of Submission: 10/21/20
 *
 * options.c
 */
	
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "options.h"

char get_state_character(int pid) {
    // -s
    char stat_proc_string[100];
    sprintf(stat_proc_string, "/proc");
    DIR* stat_dir = opendir(stat_proc_string);
    if (stat_dir != NULL)
    {
        struct dirent* entry;
        while (entry = readdir(stat_dir))
        {
            if (strtol(entry->d_name, NULL, 10) == pid)
            {
                char stat_string[25];
                sprintf(stat_string, "/proc/%d/stat", pid);
                FILE* stat_file = fopen(stat_string, "r");
                char state;
                fscanf(stat_file, "%*d %*s %c", &state);
                fclose(stat_file);
                return state;
            }
        }
    }
}

void assign_time(int pid, char* ret) { 
    // -t
    char stat_proc_string[100];
    sprintf(stat_proc_string, "/proc");
    DIR* stat_dir = opendir(stat_proc_string);
    if (stat_dir != NULL)
    {
        struct dirent* entry;
        // parse stat for single-character state
        while (entry = readdir(stat_dir))
        {
            if (strtol(entry->d_name, NULL, 10) == pid)
            {
                char stat_string[25];
                sprintf(stat_string, "/proc/%d/stat", pid);
                FILE* stat_file = fopen(stat_string, "r");
                char dummy;
                long unsigned int utime, stime;
                fscanf(stat_file, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu");
                fscanf(stat_file, "%lu %lu", &utime, &stime);
                fclose(stat_file);
                long unsigned int hours, minutes, seconds, total_seconds = (utime + stime) / (long unsigned int)sysconf(_SC_CLK_TCK);
                hours = total_seconds / 3600;
                minutes = (total_seconds - (3600 * hours)) / 60;
                seconds = total_seconds - (3600 * hours) - (minutes * 60);
                char hh[3], mm[3], ss[3];
                if (hours < 10)
                    sprintf(hh, "0%lu", hours);
                else
                    sprintf(hh, "%lu", hours);
                if (minutes < 10)
                    sprintf(mm, "0%lu", minutes);
                else
                    sprintf(mm, "%lu", minutes);
                if (seconds < 10)
                    sprintf(ss, "0%lu", seconds);
                else
                    sprintf(ss, "%lu", seconds);
                sprintf(ret, "%s:%s:%s", hh, mm, ss);
            }
        }
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
