/* 
/	Brief: This includes the implementation of the two threads (1 & 2) including semaphores, 
/	These thread process a output.txt file which inlcudes the average waiting time and turn-around time
/
/  	Author: Dakota Harkins
/  	Date: 29/04/2018
*/

#ifndef THREADS_H
#define THREADS_H

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

#include "Processes.h"

//Initialses threads, semaphores, mutexes and shared variables
void initialiseThreads();

//Thread 1 function: reads from file and passes to pipe
void *thread1(void *arg);

//Thread 2 function: reads from pipe and passes to global struct
void *thread2(void *arg);

//Run the threads
void runThreads();

#endif
