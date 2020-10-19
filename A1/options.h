#define OPTIONS_H_
//-s
char return_state_character(int pid);

//-t
char* return_uptime(int pid);

//-v
char* return_virtual_mem(int pid);

//-c
char* return_command_line(int pid);
