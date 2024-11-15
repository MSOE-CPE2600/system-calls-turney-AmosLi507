// Amos(Mohan) Li
// Lab 9 System Calls
// CPE 2600 121
// Prof. Turney
// 11/15/2024
// pinfo.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    pid_t pid;

    if(argc == 2) {
        pid = atoi(argv[1]);
    } else {
        pid = getpid(); //use current proccess ID
    }

    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        perror("Error getting priority.");
        return 1;
    } else {
        printf("Process ID: %d.\n", pid);
        printf("Priority: %d.\n", priority);
    }

    int scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {   
        perror("Error getting scheduler.");
        return 1;
    }

    const char* scheduler_name;
    switch (scheduler) {
        case SCHED_OTHER:
            scheduler_name = "SCHED_OTHER";
            break;
        case SCHED_FIFO:
            scheduler_name = "SCHED_FIFO";
            break;
        case SCHED_RR:
            scheduler_name = "SCHED_RR";
            break;
        case SCHED_BATCH:
            scheduler_name = "SCHED_BATCH";
            break;
        case SCHED_IDLE:
            scheduler_name = "SCHED_IDLE";
            break;
        case SCHED_DEADLINE:
            scheduler_name = "SCHED_DEADLINE";
            break;
        default:
            scheduler_name = "UNKNOWN";
    }

    printf("Scheduler: %s.\n", scheduler_name);

    return 0;
}