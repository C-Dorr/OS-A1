/*
 * Chris Dorr & Jordyn Marlow
 * scheduler.h
 */

#define SCHEDULER_H_
    
void timer_handler(int signal);
void timer_init();

void handle_process(int signal, int pid, int priority);

//Display first time scheduled process information
void begin_process_statement(int proc_num, int priority, int pid, long unsigned int value);

//Display process information when process is suspended
void suspend_process_statement(int proc_num, int priority, int pid, long unsigned int prime);

//Display process information when process is resumed
void resume_process_statement(int proc_num, int priority, int pid, long unsigned int prime);


//Display process information when process is finished
void finished_process_statement(int proc_num, int priority, int pid, long unsigned int prime);

