/* 
/	Brief: simulate CPU scheduling by applying shortest-remaining-time-first algorithm. 		measure average waiting time and turn around time in the CPU scheduling
/
/  	Author: Dakota Harkins
/  	Date: 29/04/2018
*/

#include "Threads.h"

int main() {

    //1. initialise all components
    initialiseThreads();

    //2. run program
    runThreads();

    return EXIT_SUCCESS;
}
