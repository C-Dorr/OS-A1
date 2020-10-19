/*
 * Author: Chris Dorr & Jordyn Marlow
 * Assignment Number: 1
 * Date of Submission:
 * options.c
 */

#include <stdio.h>
#include "options.h"

char return_state_character(int pid) {
    return 'c';
}

char* return_uptime(int pid) {
    return "UPTIME";
}

char* return_virtual_mem(int pid) {
    return "VMEM";
}

char* return_command_line(int pid) {
    return "CMDLINE";
}
