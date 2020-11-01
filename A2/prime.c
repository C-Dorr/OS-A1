#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

long unsigned int calculatedPrime = 123400003;
long unsigned int highestPrime = calculatedPrime;
bool paused = false, terminated = false;
int proc_num, priority;

void print_id();
void print_status();
void handler(int signum);
int checkPrimeAndPrint(unsigned long int toCheck);

// argv must contain process number and priority
int main(int argc, char *argv[])
{
	print_id();
	printf("I just got started. I am starting with the number %lu to find the next prime number.\n\n", calculatedPrime);
	
	proc_num = argv[0];
	priority = argv[1];
	
	signal(SIGTERM, handler);
	signal(SIGCONT, handler);
	signal(SIGTSTP, handler);
	
	int numPrinted = 0;
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
			while (numPrinted < 10)
			{
				if (checkPrimeAndPrint(numberToCheck) == 1)
				{
					highestPrime = numberToCheck;
					printf("prime number is %lu \n", highestPrime);
					numPrinted++;
				}
				numberToCheck++;
			}
		}
	}
}

void print_id()
{
	printf("Process %d: My priority is %d, my PID is %d: ", proc_num, priority, getpid());
}

void print_status(char* status)
{
	print_id();
	printf(" %s ", status);
	printf("Highest prime number I found is %lu. ", highestPrime);
}

void handler(int signal)
{
	// write handler code here
	switch(signal)
	{
		case(SIGTSTP):
			// suspend process
			print_status("I just got resumed.");
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

int checkPrimeAndPrint(unsigned long int toCheck)
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









