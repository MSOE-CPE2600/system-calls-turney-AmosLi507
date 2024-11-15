// Amos(Mohan) Li
// Lab 9 System Calls
// CPE 2600 121
// Prof. Turney
// 11/15/2024
// info.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

/*
* Information maintenance system calls provide data concerning
* the entire running system.
* parameter - argc argument count
* parameter - argv[] argument array address
*/
int main(int argc, char* argv[]) {

    //current time
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == 0) {
        printf("Current time of day is %lld nanoseconds since Jan 1, 1970.\n", (long long)(ts.tv_sec *1e9 + ts.tv_nsec));
        printf("%lld is the number of nanoseconds into the current second.\n", (long long)(ts.tv_nsec));
    } else {
        perror("Failed to get time.");
    }

    //hostname
    char hostname[1024];
    if (gethostname(hostname, sizeof(hostname)) == 0 && strlen(hostname) > 0) {
        printf("Network name is %s.\n", hostname);
    } else {
        perror("Failed to get hostname.");
    }

    //OS information
    struct utsname uts;
    if (uname(&uts) == 0) {
        if (strlen(uts.sysname) > 0) {
            printf("Operating system name: %s.\n", uts.sysname);
        } 
        if (strlen(uts.release) > 0) {
            printf("Operating system release: %s.\n", uts.release);
        }
        if (strlen(uts.version) > 0) {
            printf("Operating system version: %s.\n", uts.version);
        }
        if (strlen(uts.machine) > 0) {
            printf("Hardware type: %s.\n", uts.machine);
        }
    } else {
        perror("Failed to get OS information.");
    }

    //CPU
    int nprocs = get_nprocs();
    if(nprocs > 0) {
        printf("Number of CPUs: %d.\n", nprocs);
    } else {
        perror("Failed to get # of CPUs.");
    }    

    //memory information
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        printf("Total physical memory: %lu bytes.\n", info.totalram * info.mem_unit);
        printf("Free memory: %lu bytes.\n", info.freeram * info.mem_unit);
    } else {
        perror("Failed to get memory information.");
    }

    return 0;
}