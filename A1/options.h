#define OPTIONS_H_
extern const int BUFFER_LEN;

//-s
char return_state_character(int pid);

//-t
char* return_uptime(int pid);

//-v
void return_virtual_mem(int pid, char* ret);

//-c
void return_command_line(int pid, char* ret);
