#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_PROCESSES = 1000;

struct process {
    int number; // -1 if hole is empty
    int start;
    int size;
};

int best_fit_start(int size, struct process* holes[], int process_count);
int worst_fit_start(int size, struct process* holes[], int process_count);
int first_fit_start(int size, struct process* holes[], int process_count);

int main(int argc, char *argv[]) {
    int process_count = 1;
    int memory_pointer = 0;

    int memory_size = atoi(argv[1]);
    char * input[1000];
    struct process* holes[MAX_PROCESSES];
    
    struct process empty_hole;
    empty_hole.number = -1;
    empty_hole.start = 0;
    empty_hole.size = memory_size;
    holes[0] = &empty_hole;

    while( 1 ) {

        printf("allocater> ");
        gets(input);
        char * command = strtok(input, " ");
        //Request
        if (strcmp(command, "RQ") == 0) {
			
            // parse arguments for struct fields
            int number = atoi(strtok(NULL, " ") + sizeof(char));
            int size = atoi(strtok(NULL, " "));
            int start = atoi(strtok(NULL, " "));
            char mode = strtok(NULL, "");
			
			process_count++;
            
            // according to mode, get holes[] index of new process
            int ind;
            switch (mode) {
                case 'W':
                	ind = worst_fit_start(size, holes, process_count);
                    break;
                case 'B':
                	ind = best_fit_start(size, holes, process_count);
                    break;
                case 'F':
                	ind = first_fit_start(size, holes, process_count);
                    break;
            }
            
            // shift holes/processes
            for (int i = process_count; i > ind; i++)
            {
            	holes[i] = holes[i - 1];
            }
            
			// insert new process into array
			holes[ind]->number = number;
			holes[ind]->size = size;
			holes[ind]->start = start;
			
			// decrease size of hole
			holes[ind + 1]->start += size + 1;
			holes[ind + 1]->size -= size;
            
        } else if (strcmp(command, "RL") == 0) {
        	// make process empty hole
			int num = atoi(strtok(NULL, " ") + sizeof(char));
			for(int i = 0; i < process_count; i++) {
				if (holes[i]->number == num)
				{
					holes[i]->number = -1;
				}
			}
			// should we combine with adjacent empty holes if applicable?
			
        } else if (strcmp(command, "C") == 0) {
        	// add up the sizes of all empty holes, shift start field of each process hole so they are sequential
        	
        	// remove all empty holes from array
        	
        	// add new empty hole to array
        	
        	// make sure to update process_count

        } else if (strcmp(command, "STAT") == 0) {
            
            printf("Processes: %d\n", process_count);

            for(int i = 0; i < process_count; i++) {
            	if (holes[i]->number >= 0)
            	{
                	printf("P%d: Addresses [%d:%d]\n", holes[i]->number,
                                holes[i]->start,
                                holes[i]->start + holes[i]->size);
            	}
            	else
            	{
            		printf("Unused: Addresses [%d:%d]\n",
                                holes[i]->start,
                                holes[i]->start + holes[i]->size);
            	}
            }
        } else if (strcmp(command, "X") == 0) {
            printf("Goodbye\n");
            exit(EXIT_SUCCESS);
        } else {
            printf("Please enter a valid input.\n");
        }
    }
}

int best_fit_start(int size, struct process* holes[], int process_count)
{
	// search entire array of holes for smallest hole large enough for process
}

int worst_fit_start(int size, struct process* holes[], int process_count)
{
	// search entire array of holes for largest hole large enough for process
}

int first_fit_start(int size, struct process* holes[], int process_count)
{
	// search from beginning of set of holes for first hole that is large enough for process
}




