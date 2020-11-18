#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#include <pthread.h>

const int GETOPT_FAILURE = -1;
const int TAXI_CAPACITY = 4;
/* Declare, and in some cases assign, variables to be used later */
int op, student_count, student_counter, taxi_count, taxi_counter, max_seconds;

int* ready_students;
int ready_students_count = 0;
sem_t new_student_sem;

void reset_ready_students(int size);
void print_ready_students();
void* student();
void* taxi();
void thread_task(int i);

int main(int argc, char *argv[]) {

    //Semaphore initializtion
    sem_init(&new_student_sem, 0, 0);

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
                //utime information
                max_seconds = atoi(optarg);
                break;
                /* No options. Per assignment, exit with no output. */
            default:
                exit(EXIT_FAILURE);
        }
    }
    
    ready_students = malloc(student_count * sizeof(int));
    reset_ready_students(student_count);

    /* Make threads */
    pthread_t student_threads[student_count];
    for (int i = 0;  i < student_count; i++) {
        pthread_create(&student_threads[i], NULL, student, &i);
    }

    pthread_t taxi_threads[taxi_count];
    for (int i = 0;  i < taxi_count; i++) {
        pthread_create(&taxi_threads[i], NULL, taxi, &i);
    }

    /* Makes sure the main program waits until all threads have finished */
    for (int i = 0; i < student_count; i++) {
        pthread_join(student_threads[i], NULL);
    }
    
    for (int i = 0; i < taxi_count; i++) {
        pthread_join(taxi_threads[i], NULL);
    }

    /* Exit sucessfully after processing all arguments */
    exit(EXIT_SUCCESS);
}

void reset_ready_students(int size) {
	for (int i = 0; i < size; i++) {
        ready_students[i] = -1;
    }
    ready_students_count = 0;
}

void print_ready_students() {
	printf("Driving students ");
	for (int i = 0; i < TAXI_CAPACITY; i++) {
    	printf("%d ", ready_students[i]);
	}
	printf("\n\n");
}

void shift_ready_students() {
	for (int i = 0; i < student_count; i++) {
		if (i < student_count - TAXI_CAPACITY)
			ready_students[i] = ready_students[i + TAXI_CAPACITY];
		else
			ready_students[i] = -1;
	}
}

void* student(int* i) {
    //Start
    int student_num = student_counter++;
    int time = (rand() % max_seconds) + 1;
    printf("Student %d: Partying...\n\n", student_num);
    
    //Critical
    sleep(time);
    printf("Student %d: Done, need a ride home.\n\n", student_num);
    ready_students[ready_students_count] == student_num;
    ready_students_count++;
    //new_student_flag = true;
    sem_post(&new_student_sem);

    //Exit
    pthread_exit(0);
}

void* taxi(int* i) {
    //Start
    int taxi_num = taxi_counter++;
    printf("Taxi %d: Arrived. No students to take home.\n\n", taxi_num);

    //Critical
    // if new student flag is up, then print number of students in taxi and new student flag is now down
    while (ready_students_count < 4) {
    	//if (new_student_flag) {
    	sem_wait(&new_student_sem);
		printf("Taxi %d: %d students. ", taxi_num, ready_students_count);
		print_ready_students();
		//new_student_flag = false;
    	//}
    }
    // if number of students in taxi is 4, then empty ready_students (set all values to -1)
    printf("Taxi %d: Have 4 students. ", taxi_num);
    print_ready_students();
	reset_ready_students(TAXI_CAPACITY);

    //Exit
	pthread_exit(0);
}




