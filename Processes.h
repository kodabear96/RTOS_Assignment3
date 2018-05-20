/* 
/	Brief: This includes the implementation of the two threads (1 & 2) including semaphores, 
/	These thread process a output.txt file which inlcudes the average waiting time and turn-around time
/
/  	Author: Dakota Harkins
/  	Date: 29/04/2018
*/

#ifndef PROCESSES_H
#define PROCESSES_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//creates the Processes
void createProcesses();

//Initialses threads, semaphores, mutexes and shared variables
void runAnalysis();

float getAverageTurnaroundTime();

float getAverageWaitingTime();

void simulateScheduling();



#endif
