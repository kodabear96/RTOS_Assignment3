/* 
/	Brief: This includes the implementation of the three threads (A, B & C) including semaphores, a pipe
/	These thread process a data.txt file and output a src.txt file that discludes the header
/
/  	Author: Dakota Harkins
/  	Date: 29/04/2018
*/


#include "Processes.h"

//CONSTANTS
#define numberOfProcesses 7 			//defined in assignment guidelines

//STRUCTS
typedef struct					//stores information of each process
{
  int pid;					//process id
  int arrivalTime, burstTime, remainingTime;	//process time values
}process;

process pro[8];
float averageWaitingTime, averageTurnaroundTime;

//FUNCTIONS
void simulateScheduling()
{
	//1. Create processes
	createProcesses();

	//2. Run analysis
	runAnalysis();
}

void runAnalysis() {

   	int endTime;			//the time it takes for all processes to finish
	int smallestProcess;		//the smallest current process
    	int completedProcesses=0;	//number of processes that have been completed
	int time;			//current time iteration in the logic
	int sumWaitingTime=0;		//sum of all waiting time
	int sumTurnaroundTime=0;	//sum of all turnaround time


    	printf("\nProcess\t|Turnaround Time| Waiting Time\n");

    pro[numberOfProcesses].remainingTime=9999;

	//for each increment of time starting at start time go through all process numbers
    for(time=0; completedProcesses!=numberOfProcesses; time++)
    {
	//set current smallestProcess to the last one
        smallestProcess=numberOfProcesses;
	// for each process
	int i;
        for(i=0;i<numberOfProcesses;i++)
        {
		//FIND smallestProcess
		//if process has arrived and the remaining time is smaller than the smallestProcess 			remaining time and it's greater than 0
            if(pro[i].arrivalTime<=time && pro[i].remainingTime < pro[smallestProcess].remainingTime && pro[i].remainingTime >0)
            {
		//new smallestProcess is equal to this process
                smallestProcess=i;
            }
        }

	//decrement smallestProcess
        pro[smallestProcess].remainingTime--;
	
	
        if(pro[smallestProcess].remainingTime==0)
        {
		//mark process as completed
            completedProcesses++;
		//increment endTime
            endTime=time+1;
            printf("P[%d]\t|\t%d\t|\t%d\n",pro[smallestProcess].pid,endTime-pro[smallestProcess].arrivalTime,endTime-pro[smallestProcess].burstTime-pro[smallestProcess].arrivalTime);
            sumWaitingTime+=endTime-pro[smallestProcess].burstTime-pro[smallestProcess].arrivalTime;
            sumTurnaroundTime+=endTime-pro[smallestProcess].arrivalTime;
        }
    }

 	averageWaitingTime = sumWaitingTime*1.0/numberOfProcesses;
	averageTurnaroundTime = sumTurnaroundTime*1.0/numberOfProcesses;
    	printf("\n\nAverage waiting time = %f\n",averageWaitingTime);
    	printf("Average Turnaround time = %f\n",averageTurnaroundTime);
}

void createProcesses() {
  pro[0].pid=1;pro[0].arrivalTime=8;pro[0].burstTime=10;  pro[0].remainingTime=10; 
  pro[1].pid=2;pro[1].arrivalTime=10;pro[1].burstTime=3;  pro[1].remainingTime=3; 
  pro[2].pid=3;pro[2].arrivalTime=14;pro[2].burstTime=7;  pro[2].remainingTime=7; 
  pro[3].pid=4;pro[3].arrivalTime=9;pro[3].burstTime=5;  pro[3].remainingTime=5; 
  pro[4].pid=5;pro[4].arrivalTime=16;pro[4].burstTime=4;  pro[4].remainingTime=4;
  pro[5].pid=6;pro[5].arrivalTime=21;pro[5].burstTime=6; pro[5].remainingTime=6;  
  pro[6].pid=7;pro[6].arrivalTime=26;pro[6].burstTime=2;pro[6].remainingTime=2;
}

float getAverageWaitingTime()
{
	return averageWaitingTime;
}

float getAverageTurnaroundTime()
{
	return averageTurnaroundTime;
}
