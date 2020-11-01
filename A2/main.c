#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
//#include "scheduler.h"

//Ignore thsi struct. Was for a test but we might need later based on assignment
    

int main (int argc, char* argv[]) {
    //Process Number, Arrival time, burst, and priority
    char input_line_1[] = "0 1 6 3";
    char input_line_2[] = "1 2 4 2";
    char input_line_3[] = "2 2 2 1";
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
