#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>
//#include "scheduler.h"
    
struct process {
    int number;
    int arrival_time;
    int burst;
    int priority;
    int pid;
};

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

void parse_input_file(FILE* f, struct process processes[]);

const char INPUT_PATH[] = "./input.txt";

int process_count = 0;
int zeroed_process_count = 0;

struct process process_list[100];

//curr_proc and last_proc are indexes of the processes currently and previously running on the current tick
int curr_proc;
int last_proc;

int main (int argc, char* argv[]) {

    curr_proc = -1;
    last_proc = -1;

    FILE* input_file = fopen(INPUT_PATH, "r");
    parse_input_file(input_file, process_list);
    fclose(input_file);    

    //Start scheduler clock
    timer_init();
    while(1);
}


void timer_handler(int signal) {  
    printf("TICK: %d\n", ticks);
    //Decrement burst of procedure that ran last tick
    //tick = 4
    //last_proc = 2, curr_proc = 2
    if (curr_proc >= 0) {
        process_list[curr_proc].burst--;
        if (process_list[curr_proc].burst <= 0) {
            zeroed_process_count++;
        }
    }

    if(zeroed_process_count == process_count && process_count != 0) {
        printf("exiting\n");
            exit(EXIT_SUCCESS);
    }

    last_proc = curr_proc;


/*
0 1 6 3
1 2 4 2
2 2 2 1
3 4 6 2
4 6 4 3
5 7 2 4
*/
//tick=4


    /* Assign a running process */
    //For each 
    //last_proc = curr_proc = 2
    for(int i = 0; i < process_count; i++) {
        //If the process has arrived
        if (process_list[i].arrival_time <= ticks && process_list[i].burst > 0) {

            //The first arriving process is assigned
            if (curr_proc == -1) {
                curr_proc = i;
            }

            //And this process is a higher priority than the running process
            if (process_list[curr_proc].priority > process_list[i].priority) {
                //Then change the running process to this process
                curr_proc = i;
            }

            //However if they have the same priority
            else if (process_list[curr_proc].priority == process_list[i].priority) {
                //Break the tie on sooner arrival time
                if (process_list[curr_proc].arrival_time > process_list[i].priority) {
                    curr_proc = i;
                }
            }
        }
    }

//last_proc = 2, curr_proc = 1
    if (last_proc >= 0) {
        if (process_list[last_proc].burst > 0 && last_proc != curr_proc) {
            //SUSPEND
            kill(process_list[last_proc].pid, SIGTSTP);
        } 
        if (process_list[last_proc].burst == 0) {
            //TERMINATE
            kill(process_list[last_proc].pid, SIGTERM);
            printf("%d\n", curr_proc);
        }
    }

    if (curr_proc >= 0) {
        if (process_list[curr_proc].pid < 0) {
            //NEW PROCESS
            int fork_pid = fork();

            //Child process
            if (fork_pid == 0) {
                char proc_num[10], priority_num[10];

                //Assign prime.c arguments to strings
                sprintf(proc_num, "%d", process_list[curr_proc].number);
                sprintf(priority_num, "%d", process_list[curr_proc].priority);

                //Start child process
                char* args[] = {"./prime", proc_num, priority_num, NULL};
                execvp(args[0], args);

            } 
            //Parent/Scheduler
            else if (fork_pid > 0) {
                process_list[curr_proc].pid = fork_pid;
            } 
        } else if (last_proc != curr_proc) {
            //RESUME
            kill(process_list[curr_proc].pid, SIGCONT);
        }
    }

    ticks++;
}

void timer_init() {
    struct sigaction sa;
    struct itimerval timer;

    memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = &timer_handler;
    
    sigaction(SIGALRM, &sa, NULL);
    
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec= 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec= 0;
    
    setitimer(ITIMER_REAL, &timer, NULL);   
}

void parse_input_file(FILE* f,struct process processes[]) {
    process_count = 0;
    while (fscanf(f, "%d %d %d %d\n", &processes[process_count].number, 
                                      &processes[process_count].arrival_time, 
                                      &processes[process_count].burst,  
                                      &processes[process_count].priority) != EOF) {   
        //Initilizing to a pid of -1 will let us know if the process has started
        processes[process_count].pid = -1;
        process_count++; 
    }
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

