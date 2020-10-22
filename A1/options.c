#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "options.h"

void assign_state_character(int pid, char ret) {
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
                fscanf(stat_file, "%*d %*s %c", &ret);
                fclose(stat_file);
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
                char hh[3], mm[3];
                if (hours == 0)
                    sprintf(hh, "00");
                else
                    sprintf(hh, "%lu", hours);
                if (minutes == 0)
                    sprintf(mm, "00");
                else
                    sprintf(mm, "%lu", minutes);
                sprintf(ret, "%s:%s:%lu", hh, mm, seconds);
            }
        }
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
    exit(EXIT_FAILURE);
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
    exit(EXIT_FAILURE);
}

