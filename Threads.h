/* 
/	Brief: This includes the implementation of the two threads and a FIFO
/	These threads simulate the scheduling of 7 processes using a STRF algorithm and ouput the  average waiting 		and turnaround times to a file called "output.txt"
/
/  	Author: Dakota Harkins
/  	Date: 22/05/2018
*/

#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "Processes.h"

//Initialses threads, FIFO and shared variables
void initialiseThreads();

//Thread 1 function: reads from file and passes to pipe
void *thread1(void *arg);

//Thread 2 function: reads from pipe and passes to global struct
void *thread2(void *arg);

//Signals threads to begin
void runThreads();

#endif
