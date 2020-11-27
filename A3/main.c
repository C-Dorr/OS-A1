/*
    Authors: Chris Dorr & Jordyn Marlow
    Assignment 4
    Date of Submission 11/27/2020 (Happy Thanksgiving!)
    main.c
    Given number of students, taxis, and max party time, this syncronyses
    the students and taxis, ensuring all students get home, and taxis always
    fill up to their max capacity, 4.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#include <pthread.h>

const int GETOPT_FAILURE = -1;
const int TAXI_CAPACITY = 4;

/* Declare, and in some cases assign, variables to be used later 
op: cli arguemnts
student_count:   number of students from command line
student_counter: used for student number in student threads
taxi_count: number of taxis from command line
curr_taxi: used to initialize taxi threads

ready_students: queue of students ready to leave party

ready_student_count: index of ready_students and used in taxi logic
taxi_not_ready: Assists in syncronization of taxis
*/

int op, student_count, student_counter, taxi_count, max_seconds, curr_taxi;

int* ready_students;

int ready_students_count = 0;
bool taxi_not_ready = true;


//Semaphores to ensure syncronization of taxi threads and variables
sem_t taxi_sem; 
sem_t ready_students_count_sem;
sem_t taxi_not_ready_sem;

void init_ready_students(int size); //Initialize ready_students queue and count
void print_ready_students(); //Display information about ready_students
void* student(); //Student thread code
void* taxi(); //Taxi thread code

int main(int argc, char *argv[]) {
    //Seed random so output isn't always identical
    srand(time(NULL));

    /* Loop processes all options given to program using getopt() */
    while ((op = getopt(argc, argv, "s:t:m:")) != GETOPT_FAILURE) {
        switch (op) {
            case 's':
                //Get number of students
                student_count = atoi(optarg);
                break;
            case 't':
                //Number of taxis
                taxi_count = atoi(optarg);
                break;
            case 'm':
                //Get maximum seconds 
                max_seconds = atoi(optarg);
                break;
                /* No options. Per assignment, exit with no output. */
            default:
                exit(EXIT_FAILURE);
        }
    }
    
    //Initialize ready_students to correct size and allocate values
    ready_students = malloc(student_count * sizeof(int));
    init_ready_students(student_count);

    //Prepare ready_students_count semaphore
    sem_init(&ready_students_count_sem, 0, 1);

    /* Make & Join Student threads */
    pthread_t student_threads[student_count];
    for (int i = 0;  i < student_count; i++) {
        pthread_create(&student_threads[i], NULL, student, &i);
    }


    pthread_t taxi_threads[taxi_count];

    //Create and join taxi threads as taxis arrive and depart
    for (curr_taxi = 0; curr_taxi < taxi_count; curr_taxi++) {
        //Sempaphore used later, but created and destroyed here
        //Because it relates to the creation and destruction of taxi threads
        sem_init(&taxi_sem, 0, 0);
        pthread_create(&taxi_threads[curr_taxi], NULL, taxi, &curr_taxi);
        pthread_join(taxi_threads[curr_taxi], NULL);
        sem_destroy(&taxi_sem);
    }

    //Ensure all students are done partying before exiting
    for (int i = 0; i < student_count; i++) {
        pthread_join(student_threads[i], NULL);
    }

    /* Exit sucessfully after processing threads */
    exit(EXIT_SUCCESS); 
}


/*
    init_ready_students
    Input: Max Size of ready students queue
    Output: N/A, processing function
    Initializes ready_students queue and count to useful values
*/
void init_ready_students(int size) {
	for (int i = 0; i < size; i++) {
        ready_students[i] = -1;
    }

    ready_students_count = 0;
}

/*
    print_ready_students
    Input: N/A
    Output: N/A, display function
    Displays information about the students ready for the taxi
*/
void print_ready_students() {
	printf("Driving students ");
    if(ready_students_count > 4) {
    	for (int i = 0; i < TAXI_CAPACITY; i++) {
        	printf("%d ", ready_students[i]);
    	}
    } else {
        for (int i = 0; i < ready_students_count; i++) {
            printf("%d ", ready_students[i]);
        }
    }
	printf("\n\n");
}

/*
    shift_ready_students
    Input: N/A
    Output: N/A, processing function
    After a taxi takes off, the queue must move forward for new students
*/  
void shift_ready_students() {
	for (int i = 0; i < student_count; i++) {
		if (i < student_count - TAXI_CAPACITY)
			ready_students[i] = ready_students[i + TAXI_CAPACITY];
		else
			ready_students[i] = -1;
	}

    ready_students_count -= TAXI_CAPACITY;
    taxi_not_ready = true;
}

/*
    student
    Input: Student index
    Output: N/A, thread
    thread code for partying students, waits for allocated party time and
    handles addition to ready_queue
*/
void* student(int* i) {

    int student_num = student_counter++;
    int time = (rand() % max_seconds) + 1;    

    printf("Student %d: Partying...\n\n", student_num);
    
    //Party!
    sleep(time);

    printf("Student %d: Done, need a ride home.\n\n", student_num);

    //Allow student threads to update ready_students queue FCFS
    sem_wait(&ready_students_count_sem);
    ready_students[ready_students_count] = student_num;
    ready_students_count++;
    sem_post(&ready_students_count_sem);
    
    //If there are 4 students or more, let a taxi depart with the students
    if (ready_students_count >= 4) {
        sem_wait(&taxi_not_ready_sem);
        taxi_not_ready = false;
    }
    //Let taxi loop check its information
    sem_post(&taxi_sem);

    //Exit
    pthread_exit(0);
}

/*
    taxi
    Input: Taxi index
    Output: N/A, thread
    Syncronized with student code to read ready queue and ensure that taxis
    leave with exactly 4 students who are done partying
*/
void* taxi(int* i) {

    printf("Taxi %d: Arrived. No students to take home.\n\n", curr_taxi);

    while (taxi_not_ready) {

    	sem_wait(&taxi_sem);
        sem_post(&taxi_not_ready_sem);

        if (ready_students_count  > 4) {//If two students become ready at the 
                                        //same time then ready_students_count 
                                        //would be more than 4, which a taxi
                                        //cannot carry 
		    printf("Taxi %d: %d students. ", curr_taxi, 4);
        } else {
            printf("Taxi %d: %d students. ", curr_taxi, ready_students_count);
        }

		print_ready_students();
  
    }

    printf("Taxi %d: Have 4 students, leaving. ", curr_taxi);
    print_ready_students();

    //Because taxi is leaving, adjust queue and count information
    shift_ready_students(TAXI_CAPACITY);

	pthread_exit(0);
}