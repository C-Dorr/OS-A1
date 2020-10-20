#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#include "options.h"

const char* PROC_PATH = "/proc";
const int BUFFER_LEN = 100;
/*int pid_arg = 1;
char pid [100];
itoa(pid_arg, pid, 10);
char[] pid_path = strncat("/proc/", pid);
*/

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
 
void return_virtual_mem(int pid, char* ret) {
    	
    DIR* proc = opendir(PROC_PATH);
    
    struct dirent* entry;
    
    while (entry = readdir(proc)) {
	if (strtol (entry -> d_name, NULL, 10) == pid) {
            char statm_path[BUFFER_LEN];
            sprintf(statm_path, "/proc/%d/statm", pid);
           

	    FILE* statm = fopen(statm_path, "r");
	    
	    char buffer[BUFFER_LEN];
	    fgets(buffer, 10000, statm);    
	    strcpy(ret, strtok(buffer, " "));

	    fclose(statm);
	}
    }
}

void return_command_line(int pid, char* ret) {
    DIR* proc = opendir(PROC_PATH);
    struct dirent* entry;
    while (entry = readdir(proc)) {
        if (strtol(entry -> d_name, NULL, 10) == pid) {
	    char cmdline_path[BUFFER_LEN];
            sprintf(cmdline_path, "/proc/%d/cmdline", pid);

	    FILE* cmdline = fopen(cmdline_path, "r");
	    fgets(ret, 100, cmdline);

	    fclose(cmdline);
	}
    }
}
