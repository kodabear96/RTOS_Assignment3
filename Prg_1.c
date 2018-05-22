/* 
/	Brief: simulate CPU scheduling by applying shortest-remaining-time-first algorithm. 		
/	measure average waiting time and turn around time in the CPU scheduling
/
/  	Author: Dakota Harkins
/  	Date: 22/05/2018
*/

#include "Threads.h"

int main() {

    //1. Initialise all components
    initialiseThreads();
    
    //2. Signal threads to begin
    runThreads();

    return EXIT_SUCCESS;
}
