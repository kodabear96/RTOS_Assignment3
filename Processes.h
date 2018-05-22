/* 
/	Brief: Simulates CPU scheduling by applying shortest-remaining-time-first algorithm. 		
/	Measures average waiting time and turn around time
/
/  	Author: Dakota Harkins
/  	Date: 22/05/2018
*/

#ifndef PROCESSES_H
#define PROCESSES_H

#include <stdio.h>
#include <fcntl.h>

//Creates the Processes
void createProcesses();

//Initialses threads, semaphores, mutexes and shared variables
void runAnalysis();

//Returns calculated average turnaround time
float getAverageTurnaroundTime();

//Returns calculated average waiting time
float getAverageWaitingTime();

//Simaulates the CPU scheduling
void simulateScheduling();

#endif
