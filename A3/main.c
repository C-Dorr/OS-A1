#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

const int GETOPT_FAILURE = -1;
const int TAXI_MAX = 4;
/* Declare, and in some cases assign, variables to be used later */
int op, student_count, taxi_count, max_seconds;

void student();
void taxi();
void thread_task(int i);
void student_status(int student_num, int time_left);
void taxi_status(int taxi_num, int[] current_students);

int main(int argc, char *argv[]) {

    sem_t mutex;

    /* Loop processes all options given to program using getopt() */
    while ((op = getopt(argc, argv, "s:t:m:")) != GETOPT_FAILURE) {
        switch (op) {
            case 's':
                //Get number of students
                student_count = getopt;
                break;
            case 't':
                //Number of taxis
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

    int thread_count = student_count + taxi_count;
    
    /* Make threads */
    pthread_t thread_id[thread_count];
    for (int i = 0;  i < thread_count; i++) {
        pthread_create(&thread_id[i], NULL, thread_task);
    }

    /* Makes sure the main program waits until all threads have finished */
    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_id[i], NULL);
    }

    /* Exit sucessfully after processing all arguments */
    exit(EXIT_SUCCESS);
}

void student(int max_seconds) {
    int time = (rand() % max_seconds) - 1;
}

void taxi() {
    //Dude idk
}

void thread_task(int i) {

    //Exit Thread
    pthread_exit(0);
}

void student_status(int student_num, int time_left) {
    if (time_left > 0) {
        printf("Student %d: Partying...", student_num);
    } else {
        printf("Student %d: Done, need a ride home.", student_num);
    }
}

void taxi_status(int taxi_num, int current_students[]) {
    if (sizeof(current_students) == 0) {
        printf("Taxi %d: Arrived. No students to take home.", taxi_num);
    } else {
        
        if (0 < sizeof(current_students) < student_count) {
            printf("Taxi %d: %d students. Students ", taxi_num, sizeof(current_students));
        } else if (sizeof(current_students) == TAXI_MAX) {
            printf("Taxi %d: Have 4 students. Driving students ");
        }
         for (int i = 0; i < sizeof(current_students); i++) {
            printf("%d ");
        }   
    }       
}