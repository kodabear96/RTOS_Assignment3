////************************************************////
//-----------This is the program code of L5--------////
//-----------It uses to detect deadlock process----////
////***********************************************////


#include <stdio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <errno.h>

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

/* MAIN */
int main() {

    //1. Read the data from the file
    readData();

    //2. Analyse Data
    analyseData();

    //3. Write message to file
    writeMessage();

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
    /* if it isn't deadlocked: print the order of the processes */
    if (!isDeadlocked) {
        char strLine[256] = "Order of execution: ";
        int i;
        char formatted[3];
        for (i = 0; i < numberOfProcesses; i++) {;

            sprintf(formatted, "P%d ", orderofFinishing[i]);
            strcat(strLine, formatted);
        }
        strcat(strLine, "\n");

        writeToFile(strLine);
        printf(strLine);
    }

    /* if it is deadlocked: print the deadlocked processes */
    else {
    	char strLine[256] = "Deadlocking occured due to processes: ";
    	int i;
    	char formatted2[3];
    	for(i =0; i < numberOfProcesses; i++)
    	{
        	if (!hasProcessCompleted(i))
            		sprintf(formatted2, "P%d ", i);
            		strcat(strLine, formatted2);
    		}
    		writeToFile("Deadlock Occured");
    	}
        
        /* Alert the user that the file has been written */
    printf("Writing to output_topic2.txt has finished.\n");
}

int hasProcessCompleted(int val){
    int i;
    for (i=0; i < numberOfProcesses; i++) {
        if (orderofFinishing[i] == val)
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
    fscanf(file, "%s %d %d %d %d %d %d %d %d %d", & pval, & Allocation[0][0], & Allocation[0][1], & Allocation[0][2], & Request[0][0], & Request[0][1], & Request[0][2], & Available[0], & Available[1], & Available[2]);

    /*iterate through remaining lines */
    int i;
    for (i = 1; i <= 8; i++) {
        fscanf(file, "%s %d %d %d %d %d %d", & pval, & Allocation[i][0], & Allocation[i][1], & Allocation[i][2], & Request[i][0], & Request[i][1], & Request[i][2]);
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
