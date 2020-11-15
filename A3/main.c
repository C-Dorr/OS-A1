#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

const int GETOPT_FAILURE = -1;
const int TAXI_CAPACITY = 4;
/* Declare, and in some cases assign, variables to be used later */
int op, student_count, student_counter, taxi_count, max_seconds;

int ready_students[];

void student();
void taxi();
void thread_task(int i);

int main(int argc, char *argv[]) {
    //Initialize to -1 in order to 
    //know if there is a student
    ready_students = malloc(TAXI_CAPACITY);
    
    for (int i = 0; i < TAXI_CAPACITY; i++) {
        ready_students[i] = -1;
    }

    //Semaphore initializtion
    sem_t mutex;
    sem_init(&mutex, 0, 1);

    /* Loop processes all options given to program using getopt() */
    while ((op = getopt(argc, argv, "s:t:m:")) != GETOPT_FAILURE) {
        switch (op) {
            case 's':
                //Get number of students
                student_count = atoi(getopt);
                break;
            case 't':
                //Number of taxis
                taxi_count = atoi(getopt);
                break;
            case 'm':
                //utime information
                max_seconds = atoi(getopt);
                break;
                /* No options. Per assignment, exit with no output. */
            default:
                exit(EXIT_FAILURE);
        }
    }



    /* Make threads */
    pthread_t student_threads[student_count];
    for (int i = 0;  i < student_count; i++) {
        pthread_create(&student_threads[i], NULL, student);
    }

    pthread_t taxi_threads[student_count];
    for (int i = 0;  i < taxi_count; i++) {
        pthread_create(&taxi_threads[i], NULL, taxi);
    }

    /* Makes sure the main program waits until all threads have finished */
    for (int i = 0; i < taxi_count; i++) {
        pthread_join(student_threads[i], NULL);
    }
    for (int i = 0; i < student_count; i++) {
        pthread_join(taxi_threads[i], NULL);
    }

    /* Exit sucessfully after processing all arguments */
    exit(EXIT_SUCCESS);
}

void student() {
    //Start
    int student_num = student_counter++;
    int time = (rand() % max_seconds) + 1;
    printf("Student %d: Partying...\n", student_num);
    
    //Critical
    sleep(time);

    //Exit
    printf("Student %d: Done, need a ride home.\n", student_num);
    for (int i = 0; i < TAXI_CAPACITY; i++) {
        if (ready_students[i] != -1) {
            ready_students[i] == student_num;
        }            
    }
    pthread_exit(0);
}

void taxi() {
    //Start

    //Critical

    //Exit


    /*
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
    */
}
