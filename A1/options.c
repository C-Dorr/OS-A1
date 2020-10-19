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
 
char* return_virtual_mem(int pid) {
    // -v
    char statm_proc_string[100];
    sprintf(statm_proc_string, "/proc/%d/statm", pid);
    DIR* statm = opendir(statm_proc_string);
    if (statm != NULL)
    {
        // look at first "size" field
    }
}
 
char* return_command_line(int pid) {
    // -c

    char cmdline_proc_string[100];
    sprintf(cmdline_proc_string, "/proc/%d/cmdline", pid);
    DIR* cmdline = opendir(cmdline_proc_string);
    if (cmdline != NULL)
    {
        // parse cmdline until end of string?
    }
}

