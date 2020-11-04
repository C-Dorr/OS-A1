/*
 *	Assignment 2 Scheduler & Main
 *	Authors: Christopher Dorr & Jordyn Marlow
 */

#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

const int INDEX_NOT_ASSIGNED = -1; //Represents index has not been chosen.
const int STR_LEN = 10; // Max string length

const char INPUT_PATH[] = "./input.txt"; // path to input file

// struct for info given by input file
struct process {
    int number;
    int arrival_time;
    int burst;
    int priority;
    int pid;
};

struct process process_list[100]; // array of all processes from input file

int ticks = 0; // current tick number
int process_count = 0; // total number of processes
int zeroed_process_count = 0; // number of processes that have bee terminated
int curr_proc; // process_list index of the currently running process
int last_proc; // process_list index of the process running at the last tick

// handler for SIGALRM signal from timer
void timer_handler(int signal);

// initialize timer
void timer_init();

//Print seconds tracked by scheduler
void scheduler_time();

//Display first time scheduled process information
void begin_process_statement(int proc_num, int priority, int pid);

//Display process information when process is suspended
void suspend_process_statement(int proc_num, int priority, int pid);

//Display process information when process is resumed
void resume_process_statement(int proc_num, int priority, int pid);

//Display process information when process is finished
void terminate_process_statement(int proc_num, int priority, int pid);

// parses input file, assigns contents to appropriate fields in a process struct, adds struct to process_list array
void parse_input_file(FILE* f, struct process processes[]);


int main (int argc, char* argv[]) {

	// curr_proc and last_proc do not exist yet
    curr_proc = INDEX_NOT_ASSIGNED;
    last_proc = INDEX_NOT_ASSIGNED;

	// read input file and store info in process_list
    FILE* input_file = fopen(INPUT_PATH, "r");
    parse_input_file(input_file, process_list);
    fclose(input_file);    

    //Start scheduler clock
    timer_init();
    
    // scheduler must continue running until all child processes are terminated and exit() is called
    while(1);
}

void timer_handler(int signal) {
    //
    scheduler_time();
	// new tick, curr_proc is now last_proc
	last_proc = curr_proc;
	
	// if there was a process running in the last tick
    if (last_proc >= 0) {
    	//Decrement burst of process from the last tick
        process_list[last_proc].burst--;
        // increment zeroed_process_count if process from last tick is terminated
        if (process_list[last_proc].burst <= 0) {
            zeroed_process_count++;
        }
    }
    
    // if a process was completed in the last tick
	if (last_proc >= 0 && process_list[last_proc].burst == 0) {
        terminate_process_statement(process_list[curr_proc].number,
                                        process_list[curr_proc].priority,
                                        process_list[curr_proc].pid);
        // terminate the process from the last tick
        kill(process_list[last_proc].pid, SIGTERM);
        // no currently running process anymore
        curr_proc = -1;
    }
    
    // if all processes have been terminated, exit scheduler
    if(zeroed_process_count == process_count && process_count != 0) {
        exit(EXIT_SUCCESS);
    }

    // for each process
    for(int i = 0; i < process_count; i++) {
    
        //If the process has arrived and is not terminated
        if (process_list[i].arrival_time <= ticks && process_list[i].burst > 0) {

            // if there is no running process, set curr_proc to the first valid process
            if (curr_proc == -1) {
                curr_proc = i;
            }

	        // if process at index i has a higher priority than that of curr_proc
	        if (process_list[curr_proc].priority > process_list[i].priority) {
	            // change the running process to process at index i
	            curr_proc = i;
	        }
	        // if curr_proc and proc at index i have same priority, break tie with arrival time
	        else if (process_list[curr_proc].priority == process_list[i].priority) {
	            // break the tie on sooner arrival time
	            if (process_list[curr_proc].arrival_time > process_list[i].priority) {
	                curr_proc = i;
	            }
	        }
        }
    }

	// if there was a process running at the last tick but it isn't terminated yet
    if (last_proc >= 0 && process_list[last_proc].burst > 0 && last_proc != curr_proc) {
        suspend_process_statement(process_list[last_proc].number,
                                process_list[last_proc].priority,
                                process_list[last_proc].pid);
        // send the suspend signal to the process running in the last tick
        kill(process_list[last_proc].pid, SIGTSTP);

    }

	// if there is a process running in the current tick
    if (curr_proc >= 0) {
    
    	// if the process running in the current tick does not have a pid
        if (process_list[curr_proc].pid < 0) {
        
            // fork and start new process
            int fork_pid = fork();

            //Child process
            if (fork_pid == 0) {

                begin_process_statement(process_list[curr_proc].number,
                                        process_list[curr_proc].priority,
                                        process_list[curr_proc].pid);
            
            	// pass process number and priority number to child process prime.c
                char proc_num[STR_LEN], priority_num[STR_LEN];
                
                sprintf(proc_num, "%d", process_list[curr_proc].number);
                sprintf(priority_num, "%d", process_list[curr_proc].priority);

                // start new child process
                char* args[] = {"./prime", proc_num, priority_num, NULL};
                execvp(args[0], args);
            } 
            //Parent/Scheduler
            else if (fork_pid > 0) {
            	// assign the pid returned from fork to pid field in curr_proc struct
                process_list[curr_proc].pid = fork_pid;
            } 
        }
        // if we are switching processes in this tick
        else if (last_proc != curr_proc) {
            // send resume signal to curr_proc
            resume_process_statement(process_list[curr_proc].number,
                                        process_list[curr_proc].priority,
                                        process_list[curr_proc].pid);
            kill(process_list[curr_proc].pid, SIGCONT);
        }
    }
	// increment ticks
    ticks++;
}

/* initialize timer so send SIGALRM every second */
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

/* parse input file and store data in struct array process_list */
void parse_input_file(FILE* f,struct process processes[]) {
    process_count = 0;
    while (fscanf(f, "%d %d %d %d\n", &processes[process_count].number, 
                                      &processes[process_count].arrival_time, 
                                      &processes[process_count].burst,  
                                      &processes[process_count].priority) != EOF) {   
        //Initializing to a pid of -1 will let us know the process has not started
        processes[process_count].pid = -1;
        process_count++; 
    }
}

void scheduler_time() {
    printf("Scheduler: Time now: %d seconds\n\n", ticks);
}

void begin_process_statement(int proc_num, int priority, int pid) {
    printf("Process %d: Priority %d, PID %d: STARTING\n\n", proc_num, priority, pid);
}

void suspend_process_statement(int proc_num, int priority, int pid) {
    printf("Process %d: Priority %d, PID %d: SUSPENDING\n\n", proc_num, priority, pid); 
}

//Display process information when process is resumed
void resume_process_statement(int proc_num, int priority, int pid) {
    printf("Process %d: Priority %d, PID %d, RESUMING\n\n", proc_num, priority, pid);
}

//Display process information when process is resumed
void terminate_process_statement(int proc_num, int priority, int pid) {
    printf("Process %d: Priority %d, PID %d, FINISHED\n\n", proc_num, priority, pid);
}

