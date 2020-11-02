#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
//#include "scheduler.h"
    
int ticks = 0;
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

//If two or more processes of the highest priority are ready to run, the tie
//is broken by scheduling the process with the earlier arrival time first                                                                                                                                               
int break_priority_tie(int pid1, int pid2);




int main (int argc, char* argv[]) {
    //Process Number, Arrival time, burst, and priority
    char input_line_1[] = "0 1 6 3";
    char input_line_2[] = "1 2 4 2";
    char input_line_3[] = "2 2 2 1";

    //Start scheduler clock
    timer_init();

    int pid = fork();
    
    if (pid == 0) { //Child
        char* args[] = {"./prime", "0", "1", NULL};
        execvp(args[0], args);

    } else if (pid > 0) { //Successful Parent

        sleep(2);
        //Suspend 
        kill(pid, SIGTSTP);
        sleep(1);
        //Resume
        kill(pid, SIGCONT);
        sleep(2);
        //Terminate
        kill(pid, SIGTERM);

        exit(EXIT_SUCCESS);

    } else { //Failed to fork
        exit(EXIT_FAILURE);
    }
}


void timer_handler(int signal/* info */) {
    //Start process with this info (info)
    printf("Tick %d\n", ticks++);
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

int break_priority_tie(int pid_1, int pid_2) {
    int higher_priority = pid_1;

    return higher_priority;
}
