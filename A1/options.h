/*
 * Authors: Christopher Dorr & Jordyn Marlow
 * Assignment Number: 1
 * Date of Submission: 10/21/20
 * 
 * options.h
 */

#define OPTIONS_H_
static const int BUFFER_LEN = 100;
static const int FILE_GET_SIZE = 10000;
static const char* PROC_PATH  = "/proc";

//-s
char get_state_character(int pid);

//-t
void assign_time(int pid, char* ret);

//-v
void assign_virtual_mem(int pid, char* ret);

//-c
void assign_command_line(int pid, char* ret);
