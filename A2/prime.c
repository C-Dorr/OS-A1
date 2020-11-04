/*
 *	Assignment 2 Child
 *	Authors: Christopher Dorr & Jordyn Marlow
 *  prime.c
 *  This is the child of main.c which is started based on
 *  our preemptive scheduler
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

long unsigned int calculatedPrime = 123400003;
long unsigned int highestPrime;

bool paused = false; // process has been sent suspended signal
bool terminated = false; // process has been sent terminated signal
int proc_num, priority; // process number and priority from scheduler

void print_id(); // prints process number, priority, and pid to stdout
void print_status(); // prints status (suspended, resumed, terminated)
void handler(int signum); // handler for SIGTSTP, SIGCONT, and SIGTERM signals
int checkPrime(unsigned long int toCheck);

// argv must contain process number and priority
int main(int argc, char *argv[])
{
	// initialize highestPrime as calculatedPrime
	highestPrime = calculatedPrime;
	
	// get process number and priority from argv
	proc_num = atoi(argv[1]);
	priority = atoi(argv[2]);
	
	// print 'I am starting' output statement
	print_id();
	printf("I just got started. I am starting with the number %lu to find the next prime number.\n\n", calculatedPrime);
	
	// set up SIGTERM, SIGCONT, SIGTSTP signals to trigger handler function
	signal(SIGTERM, handler);
	signal(SIGCONT, handler);
	signal(SIGTSTP, handler);
	
	long unsigned int numberToCheck = calculatedPrime + 1;
	while (!terminated)
	{
		if (paused)
		{
			// if pause signal has been received, pause the process
			pause();
		}
		else
		{
			// if no pause signal has been received, continue finding prime number
			if (checkPrime(numberToCheck) == 1)
			{
				highestPrime = numberToCheck;
				//printf("Prime number is %lu \n", highestPrime);
			}
			numberToCheck++;
		}
	}
	exit(EXIT_SUCCESS);
}

/* prints process number, priority, and pid to stdout */
void print_id()
{	
	printf("Process %d: My priority is %d, my PID is %d: ", proc_num, priority, getpid());
}

/* prints status (suspended, resumed, terminated) */
void print_status(char* status)
{
	print_id();
	printf("%s", status);
	printf(" Highest prime number I found is %lu.\n\n", highestPrime);
}

/* handler for SIGTSTP, SIGCONT, and SIGTERM signals */
void handler(int signal)
{
	// write handler code here
	switch(signal)
	{
		case(SIGTSTP):
			// suspend process
			print_status("I just got suspended.");
			paused = true;
			break;
		case(SIGCONT):
			// resume process
			print_status("I just got resumed.");
			paused = false;
			break;
		case(SIGTERM):
			// terminate process
			print_status("I completed my task and I am exiting.");
			terminated = true;
			break;
	}
}

int checkPrime(unsigned long int toCheck)
{
	unsigned long int i = 2;
	int prime = 1;
	while (prime == 1 && i < toCheck / 2)
	{
		if (toCheck % i == 0)
			prime = 0;
		i++;
	}
	return prime;
}

