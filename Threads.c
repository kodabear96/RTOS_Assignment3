/* 
/	Brief: This includes the implementation of the two threads and a FIFO
/	These threads simulate the scheduling of 7 processes using a STRF algorithm and ouput the  average waiting 		and turnaround times to a file called "output.txt"
/
/  	Author: Dakota Harkins
/  	Date: 22/05/2018
*/


#include "Threads.h"

//CONSTANTS
#define FIFONAME "FIFO" 			//Name of the FIFO
pthread_t threadId1, threadId2; 	//thread definitions

//FUNCTIONS
void initialiseThreads() {

        /* Unlink and create FIFO */
        unlink(FIFONAME);
        if (mkfifo(FIFONAME, S_IRWXU) < 0) {
                exit(1);
        }

        /* Create threads */
        if (pthread_create( & threadId1, NULL, & thread1, NULL)) {
                perror("Thread 1 init failed");
                exit(1);
        }

        if (pthread_create( & threadId2, NULL, & thread2, NULL)) {
                perror("Thread 2 init failed");
                exit(1);
        }
}

void * thread1(void * arg) {

        /* 1. Run scheduling */
        simulateScheduling();

        /* 2. Retrieve average times */
        float averageWaitingTime = getAverageWaitingTime();
        float averageTurnaroundTime = getAverageTurnaroundTime();

        /* 3. Format average times */
        char averageData[50];
        sprintf(averageData, "Average Wait-time: %f\n Average Turnaround-time: %f", averageWaitingTime,
                averageTurnaroundTime);

        /* 4. Open FIFO */
        int fd;
        if ((fd = open(FIFONAME, O_WRONLY)) < 0) {
                perror("Opening FIFO:");
                exit(1);
        }

        /* 5. Write data to FIFO */
        write(fd, & averageData, strlen(averageData));

        /* 6. Close FIFO */
        close(fd);

}

void * thread2(void * arg) {

        /* 1. Open file */
        FILE * file;
        file = fopen("output.txt", "w");
        if (file == NULL) {
                perror("Write file failed to open");
                exit(1);
        }

        /* 2. Open FIFO */
        int fd;
        if ((fd = open(FIFONAME, O_RDONLY)) < 0) {
                perror("open2");
                exit(1);
        }

        /* 3. Read from FIFO */
        char data[60];
        int n = read(fd, data, 60);
        if (n == 0) {
                exit(1);
        }

        /* 4. Close and Unlink FIFO */
        close(fd);
        unlink(FIFONAME);

        /* 5. Write to file*/
        fprintf(file, "%s", data);
}

void runThreads() {

        /* Signal Thread 2 to start */
        pthread_join(threadId2, NULL);
}

