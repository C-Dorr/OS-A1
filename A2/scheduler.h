/*
 * Chris Dorr & Jordyn Marlow
 * scheduler.h
 */

#define SCHEDULER_H_

//struct itimerval timer;

//Display first time scheduled process information
void begin_process_statement(int proc_num, int priority, int pid, long unsigned int value);

//Display process information when process is suspended
void suspend_process_statement(int proc_num, int priority, int pid, long unsigned int prime);

//Display process information when process is resumed
void resume_process_statement(int proc_num, int priority, int pid, long unsigned int prime);


//Display process information when process is finished
void finished_process_statement(int proc_num, int priority, int pid, long unsigned int prime);

//If two or more processes of the highest priority are ready to run, the tie
//is broken by scheduling the process with the earlier arrival time first
int break_priority_tie(int pid1, int pid2);



