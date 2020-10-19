#include <stdio.h>
#include <string.h>
#include "options.h"


int pid_arg = 1;
char pid [100];
itoa(pid_arg, pid, 10);
char[] pid_path = strncat("/proc/", pid);

char return_state_character(int pid) {
    // -s
    DIR* stat = opendir(strncat(pid_path, "/stat"));
    if (stat != NULL)
    {
        entry = readdir(stat);
        // parse stat for single-character state
    }
}
    
char* return_uptime(int pid) { 
// -t
    DIR* stat = opendir(strncat(pid_path, "/stat"));
    if (stat != NULL)
    {
        entry = readdir(stat);
        // add utime to stime and display in hh:mm:ss
    }
}
 
char* return_virtual_mem(int pid) {
    // -v
    DIR* statm = opendir(strncat(pid_path, "/statm"));
    if (statm != NULL)
    {
        entry = readdir(statm);
        // look at first "size" field
    }
}
 
char* return_command_line(int pid) {
    // -c
    DIR* cmdline = opendir(strncat(pid_path, "/cmdline"));
    if (cmdline != NULL)
    {
        entry = readdir(cmdline);
        // parse cmdline until end of string?
    }
}
