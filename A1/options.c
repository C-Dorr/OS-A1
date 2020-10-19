#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#include "options.h"


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
    // -v
    char statm_proc_string[100];
    sprintf(statm_proc_string, "/proc/%d/statm", pid);

    FILE* statm = fopen(statm_proc_string, "r");
    char c = fgetc(statm);

    while (c != EOF && c != ' ') {
	if (c != ' ') {
            strcat(ret, &c);
        }
	c = fgetc(statm);
    }
}
 
void return_command_line(int pid, char* ret) {
    // -c
    char cmdline_proc_string[100];
    sprintf(cmdline_proc_string, "/proc/%d/cmdline", pid);

    FILE* cmdline = fopen(cmdline_proc_string, "r");
    fgets(ret, 100, cmdline);
}

