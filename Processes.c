/* 
/	Brief: Simulates CPU scheduling by applying shortest-remaining-time-first algorithm. 		
/	Measures average waiting time and turn around time
/
/  	Author: Dakota Harkins
/  	Date: 22/05/2018
*/


#include "Processes.h"

//CONSTANTS
#define numberOfProcesses 7 				//Defined in assignment guidelines

//STRUCTS
typedef struct 						//Stores information of each process
{
        int pid; 					//Process ID
        int arrivalTime, burstTime, remainingTime; 	//Process time values
}
process;

process pro[8]; 
							//Array of processes
//GLOBALS
float averageWaitingTime, averageTurnaroundTime; 	//Final data to be returned	

//FUNCTIONS
void simulateScheduling() {
        /* 1. Create processes */
        createProcesses();

        /* 2. Run analysis */
        runAnalysis();
}

void runAnalysis() {

        /* 1. Define Variables */
        int endTime; 			//the time it takes for all processes to finish
        int smallestProcess; 		//the smallest current process
        int completedProcesses = 0; 	//number of processes that have been completed
        int time; 			//current time iteration in the logic
        int sumWaitingTime = 0; 	//sum of all waiting time
        int sumTurnaroundTime = 0; 	//sum of all turnaround time

        /* 2. Initialse maximum time to be infinite */
        pro[numberOfProcesses].remainingTime = 9999;

        /* 3. Repeat until all processes completed */
        for (time = 0; completedProcesses != numberOfProcesses; time++) {
                smallestProcess = numberOfProcesses;

                /* Find the smallest process */
                int i;
                for (i = 0; i < numberOfProcesses; i++) {
                        if (pro[i].arrivalTime <= time && pro[i].remainingTime < pro[smallestProcess].remainingTime && pro[i].remainingTime > 0) {
                                smallestProcess = i;
                        }
                }

                /* Decrement smallestProcess */
                pro[smallestProcess].remainingTime--;

                /* If the process is finished */
                if (pro[smallestProcess].remainingTime == 0) {
                        /* mark process as completed */
                        completedProcesses++;
                        endTime = time + 1;
                        sumWaitingTime += endTime - pro[smallestProcess].burstTime - pro[smallestProcess].arrivalTime;
                        sumTurnaroundTime += endTime - pro[smallestProcess].arrivalTime;
                }
        }

        /* 4. Calculate averages */
        averageWaitingTime = sumWaitingTime * 1.0 / numberOfProcesses;
        averageTurnaroundTime = sumTurnaroundTime * 1.0 / numberOfProcesses;
}

void createProcesses() {
        /* Creates array of processes as defined in assignment specifications */
        pro[0].pid = 1;pro[0].arrivalTime = 8;pro[0].burstTime = 10;pro[0].remainingTime = 10;
        pro[1].pid = 2;pro[1].arrivalTime = 10;pro[1].burstTime = 3;pro[1].remainingTime = 3;
        pro[2].pid = 3;pro[2].arrivalTime = 14;pro[2].burstTime = 7;pro[2].remainingTime = 7;
        pro[3].pid = 4;pro[3].arrivalTime = 9;pro[3].burstTime = 5;pro[3].remainingTime = 5;
        pro[4].pid = 5;pro[4].arrivalTime = 16;pro[4].burstTime = 4;pro[4].remainingTime = 4;
        pro[5].pid = 6;pro[5].arrivalTime = 21;pro[5].burstTime = 6;pro[5].remainingTime = 6;
        pro[6].pid = 7;pro[6].arrivalTime = 26;pro[6].burstTime = 2;pro[6].remainingTime = 2;
}

float getAverageWaitingTime() {
        return averageWaitingTime;
}

float getAverageTurnaroundTime() {
        return averageTurnaroundTime;
}
