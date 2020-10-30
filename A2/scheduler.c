/*
 * Chris Dorr & Jordyn Marlow
 * scheduler.c
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct timer {
    clock_t start_val;
    clock_t curr_val;
    clock_t elapsed_val;
};

void timer_init(struct timer t) {
  t.start_val = clock();
  printf("Started clock.\n");
}

void timer_print(struct timer t) {
  t.curr_val = clock();
  t.elapsed_val = t.curr_val - t.start_val;

  printf("Currently %lu, %lu has elapsed.\n", t.curr_val, t.elapsed_val );
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

int break_priority_tie(int pid_1, int pid_2) {
    int higher_priority = pid_1;

    return higher_priority;
}
