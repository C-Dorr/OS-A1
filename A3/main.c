#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int GETOPT_FAILURE = -1;

int main(int argc, char *argv[]) {
    
    /* Declare, and in some cases assign, variables to be used later */
    int op, student_count, taxi_count, max_seconds;

    /* Loop processes all options given to program using getopt() */
    while ((op = getopt(argc, argv, "s:t:m:")) != GETOPT_FAILURE) {
        switch (op) {
            case 's':
                //Display PID when given PID value as argument
                student_count = getopt;
                break;
            case 't':
                taxi_count = getopt;
                break;
            case 'm':
                //utime information
                max_seconds = getopt;
                break;
                /* No options. Per assignment, exit with no output. */
            default:
                exit(EXIT_FAILURE);
        }
    }
    
    /* Exit sucessfully after processing all arguments */
    exit(EXIT_SUCCESS);
}