#define OPTIONS_H_
static const int BUFFER_LEN = 100;
//-s
void assign_state_character(int pid, char ret);

//-t
void assign_time(int pid, char* ret);

//-v
char* return_virtual_mem(int pid);

//-c
char* return_command_line(int pid);
