/* 
/	Brief: This includes the implementation of the three threads (A, B & C) including semaphores, a pipe
/	These thread process a data.txt file and output a src.txt file that discludes the header
/
/  	Author: Dakota Harkins
/  	Date: 29/04/2018
*/


#include "Threads.h"

//CONSTANTS
#define numberOfProcesses 7 			//defined in the 

//STRUCTS
typedef struct					//stores information of each process
{
  int pid;					//process id
  int arrivalTime, burstTime, remainingTime;	//process time values
}process;

//GLOBALS
sem_t Semaphore_1, Semaphore_2; // Semaphores that control threads
pthread_t threadId1, threadId2; //Thread Ids

process pro[8];

//FUNCTIONS
void initialiseThreads() {

    /* Initialise semaphores and set to 0 */
    if (sem_init( &Semaphore_1, 0, 0)) {
        perror("Failed to initialise semaphore 1");
        exit(EXIT_FAILURE);
    };

    if (sem_init( &Semaphore_2, 0, 0)) {
        perror("Failed to initialise semaphore 2");
        exit(EXIT_FAILURE);
    };

    /* Create thread attributes */
    pthread_attr_t attr;

    /* Initialise thread attributes */
    if (pthread_attr_init( & attr)) {
        perror("Failed to initialise thread attributes");
        exit(EXIT_FAILURE);
    };

    /* Create threads */
    if (pthread_create( & threadId1, & attr, & thread1, NULL)) {
        perror("Failed to initialise thread 1");
        exit(EXIT_FAILURE);
    };

    if (pthread_create( & threadId2, & attr, & thread2, NULL)) {
        perror("Failed to initialise thread 2");
        exit(EXIT_FAILURE);
    };

    /* Destroy thread attributes */
    if (pthread_attr_destroy( & attr)) {
        perror("Failed to destroy thread attributes");
        exit(EXIT_FAILURE);
    };
}

void * thread1(void * arg) {

    /* Wait for Semaphore_1 */
    sem_wait( & Semaphore_1);

	printf("Thread 1 is starting\n");

	simulateScheduling();

	printf("TODO: save doubles to FIFO\n");

	printf("Thread 1 has finished. Signalling Thread 2\n");

    /* Signal thread B */
    sem_post( & Semaphore_2);

    return EXIT_SUCCESS;
}

void * thread2(void * arg) {

    /* Wait for Semaphore_2 */
    sem_wait( & Semaphore_2);

	printf("Thread 2 started.\n");
	printf("TODO: read doubels from FIFO\n");

    return EXIT_SUCCESS;
}

void runThreads() {

    /* Signal Thread 1 to start */
    sem_post( & Semaphore_1);

    /* Wait for thread termination and status */
    void * threadResult;
    if (pthread_join(threadId1, & threadResult)) {
        errno = * ((int * ) threadResult);
        perror("Thread 1 failed");
        exit(EXIT_FAILURE);
    } else if (pthread_join(threadId2, & threadResult)) {
        errno = * ((int * ) threadResult);
        perror("Thread 2 failed");
        exit(EXIT_FAILURE);
    free(threadResult);
}
}
