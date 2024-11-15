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

int main() {
    int nice_value = 10; 
    if (nice(nice_value) == -1) {
        perror("Failed to set nice value");
        return 1;
    }

    struct timespec req;
    req.tv_sec = 1;
    req.tv_nsec = 837272638;

    if (nanosleep(&req, NULL) < 0) {
        perror("nanosleep failed");
        return 1;
    }

    printf("Goodbye!\n");

    return 0;
}
