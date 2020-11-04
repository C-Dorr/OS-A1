/*
 * Chris Dorr & Jordyn Marlow
 * scheduler.c
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>


void timer_handler(int signal/* info */) {
  //Start process with this info (info)
}

void timer_init() {
    struct sigaction sa;
    struct itimerval timer;

    memset(&timer, 0, sizeof(sa));
    
    sa.sa_handler = &timer_handler;
    
    sigaction(SIGALRM, &sa, NULL);
    
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec= 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec= 0;
    
    setitimer(ITIMER_REAL, &timer, NULL);   
}

void begin_process_information(int proc_num, int priority, int pid, long unsigned int value) {
	printf("Process %d: Priority %d, PID %d: STARTING\n Beginning" 
		   "value: %lu \n", proc_num, priority, pid, value);
}

void suspend_process_statement(int proc_num, int priority, int pid, long unsigned int prime) {
    printf("Process %d: Priority %d, PID %d: SUSPENDING\nHighest prime found: "
           "%lu \n", proc_num, priority, pid, prime); 
}

//Display process information when process is resumed
void resume_process_statement(int proc_num, int priority, int pid, long unsigned int prime) {
    printf("Process %d: Priority %d, PID %d, RESUMING\nHighest prime found: "
           "%lu\n", proc_num, priority, pid, prime);
}

//Display process information when process is resumed
void finished_process_statement(int proc_num, int priority, int pid, long unsigned int prime) {
    printf("Process %d: Priority %d, PID %d, FINISHED\nHighest prime found: "
           "%lu\n", proc_num, priority, pid, prime);
}