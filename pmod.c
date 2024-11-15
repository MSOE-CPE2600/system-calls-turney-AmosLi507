// Amos(Mohan) Li
// Lab 9 System Calls
// CPE 2600 121
// Prof. Turney
// 11/15/2024
// pmod.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>

/*
* Altering a Process
* This function modifies the priority and sleeps for 1,837,272,638 nano seconds
* parameter - argc argument count
* parameter - argv[] argument array address
*/
int main() {
    int nice_value = 10; //sets positive nice_value to reduce the priority
    if (nice(nice_value) == -1) {
        perror("Failed to set nice value"); //error message
        return 1;
    }

    struct timespec req;
    req.tv_sec = 1;
    req.tv_nsec = 837272638; //sets up the time

    if (nanosleep(&req, NULL) < 0) {
        perror("nanosleep failed"); //error message
        return 1;
    }

    printf("Goodbye!\n"); //prints goodbye

    return 0;
}
