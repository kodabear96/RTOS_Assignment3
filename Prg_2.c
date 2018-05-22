/* 
/	Brief: Utilises deadlock detection to report all possible deadlock or the sequence of process execution
/	Reads process data from "Topic2_Prg_2.txt" and writes the result to "output_topic2.txt"
/
/  	Author: Dakota Harkins
/  	Date: 22/05/2018
*/

#include <stdio.h>  
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <errno.h>
#include <signal.h>

int Request[9][3]; //the process request
int Allocation[9][3]; // already allocate resources to process
int Available[3]; //available instances for each resource

int numberOfProcesses = 9;
int numberOfResources = 3; //the no. of process and resource

int isDeadlocked = 0;

int orderofFinishing[9];
int numberOfProcessesFinished = 0;    

/* FUNCTION DECLARATIONS */
void readData();
void writeMessage();
void writeToFile(char * strLine);
void analyseData();
int hasProcessCompleted(int val);
void  SIGhandler(int);

/* MAIN */
int main() {

    //1.define signal handler
    signal(SIGUSR1, SIGhandler);               

    //2. Read the data from the file
    readData();

    //3. Analyse Data
    analyseData();

    //4. Write message to file
    writeMessage();

    //5. Raise completed signal
    raise(SIGUSR1);
    return 0;
}

void writeToFile(char * strLine) {

    /* Open new file or overwite existing */
    FILE * file = fopen("output_topic2.txt", "w");
    
    if (file == NULL) {
        perror("Failed to source or open a new file");
        exit(EXIT_FAILURE);
    };

    /* Write line to file */
    fprintf(file, "%s", strLine);

    /* Close the file */
    fclose(file);

}

void writeMessage() {
	char strLine[256] = "";
	int i;
        char formatted[3];
        
    /* if it isn't deadlocked: print the order of the processes */
    if (!isDeadlocked) {
    
        strcat(strLine, "Order of execution: ");
         
        for (i = 0; i < numberOfProcesses; i++) {;

            sprintf(formatted, "P%d ", orderofFinishing[i]);
            strcat(strLine, formatted);
        }
    }

    /* if it is deadlocked: print the deadlocked processes */
    else {
    	strcat(strLine, "Deadlocking occured due to processes: ");
	
    	for(i =0; i < numberOfProcesses; i++)
    	{
        	if (hasProcessCompleted(i) == 0)
        	{
            		sprintf(formatted, "P%d ", i);
            		strcat(strLine, formatted);
    		}
    	}
    }

    writeToFile(strLine);
}

int hasProcessCompleted(int processId){
    int i;
    for (i=0; i < numberOfProcessesFinished; i++) {
        if (orderofFinishing[i] == processId)
            return 1;
    }
    return 0;
}

void readData() {
    /* Open data.txt file */
    FILE * file = fopen("Topic2_Prg_2.txt", "r");
    if (file == 0) {
        printf("Cannot open file Topic2_Prg_2.txt");
        exit(EXIT_FAILURE);
    }

    /* Disclude the first two lines of data */
    char strLine[256];
    fgets(strLine, sizeof strLine, file);
    fgets(strLine, sizeof strLine, file);

    char pval[2];
    /*first line includes available data so has to be handled separately */
    fscanf(file, "%s %d %d %d %d %d %d %d %d %d", pval, &Allocation[0][0], &Allocation[0][1], &Allocation[0][2], &Request[0][0], &Request[0][1], &Request[0][2], &Available[0], &Available[1], &Available[2]);

    /*iterate through remaining lines */
    int i;
    for (i = 1; i <= 8; i++) {
        fscanf(file, "%s %d %d %d %d %d %d", pval, &Allocation[i][0], &Allocation[i][1], &Allocation[i][2], &Request[i][0], &Request[i][1], &Request[i][2]);
    }
}

void analyseData() {
    int isProcessFinished[numberOfProcesses];
    int currentProcess;

    /* checking if all resources required are 0 */
    for (currentProcess = 0; currentProcess < numberOfProcesses; ++currentProcess) {
        isProcessFinished[currentProcess] = 0;
        int emptyRequests = 0;
        int currentResource;

        for (currentResource = 0; currentResource < numberOfResources; ++currentResource) {
            if (!Allocation[currentProcess][currentResource]) {
                ++emptyRequests;
            }
        }
        if (emptyRequests >= numberOfResources) {
            isProcessFinished[currentProcess] = 1;
            orderofFinishing[numberOfProcessesFinished] = currentProcess;
            numberOfProcessesFinished++;

        }
    }
    int numberProcessesFinished = 0;
    while (!isDeadlocked && numberProcessesFinished < numberOfProcesses) {

        /* Iterate through all non-finished processes */
        for (currentProcess = 0; currentProcess < numberOfProcesses; ++currentProcess) {
            if (!isProcessFinished[currentProcess]) {
                int isWaiting = 0;
                int currentResource;
                for (currentResource = 0; currentResource < numberOfResources && !isWaiting; ++currentResource) {
                    if (Request[currentProcess][currentResource] > Available[currentResource]) {
                        isWaiting = 1;
                    }
                }
                if (!isWaiting) {
                    int currentResource;
                    for (currentResource = 0; currentResource < numberOfResources; ++currentResource) {
                        Available[currentResource] += Allocation[currentProcess][currentResource];
                    }
                    isProcessFinished[currentProcess] = 1;
                    orderofFinishing[numberOfProcessesFinished] = currentProcess;
                    numberOfProcessesFinished++;
                }
            }
        }
        int currentFinished = 0;
        int currentProcess;
        for (currentProcess = 0; currentProcess < numberOfProcesses; ++currentProcess) {
            if (isProcessFinished[currentProcess]) {

                ++currentFinished;
            }
        }
        isDeadlocked = (currentFinished == numberProcessesFinished);
        numberProcessesFinished = currentFinished;
    }
}

void  SIGhandler(int sig)
{
     printf("Writing to output_topic2.txt has finished.\n");
}
