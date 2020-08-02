//
// Created by orian on 01/08/2020.
//
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>
#include <syscall.h>
#include <stdint.h>
#include <sys/types.h>

struct sched_attr {
    uint32_t size;              /* Size of this structure */
    uint32_t sched_policy;      /* Policy (SCHED_*) */
    uint64_t sched_flags;       /* Flags */
    int32_t sched_nice;         /* Nice value (SCHED_OTHER, SCHED_BATCH) */
    uint32_t sched_priority;    /* Static priority (SCHED_FIFO, SCHED_RR) */
    /* Remaining fields are for SCHED_DEADLINE */
    uint64_t sched_runtime;
    uint64_t sched_deadline;
    uint64_t sched_period;
};

static int sched_setattr (pid_t pid, const struct sched_attr *attr, unsigned int flags)
{
    return syscall (SYS_sched_setattr, pid, attr, flags);
}

/**
 * Run with SUDO.
 *                  SCHED_OTHER->0,SCHED_FIFO->1,SCHED_RR->2.
 * Priority Ranges: 0             ,1-99         ,1-99
 * for SCHED->DEADLINE need use attriute.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc , char* argv[]){

    printf("Program pid:%d\n",getpid());
    printf("Valid priority range for SCHED_OTHER: %d - %d\n",
            sched_get_priority_min(SCHED_OTHER),
            sched_get_priority_max(SCHED_OTHER));
    printf("Valid priority range for SCHED_FIFO: %d - %d\n",
           sched_get_priority_min(SCHED_FIFO),
           sched_get_priority_max(SCHED_FIFO));
    printf("Valid priority range for SCHED_RR: %d - %d\n",
           sched_get_priority_min(SCHED_RR),
           sched_get_priority_max(SCHED_RR));
    printf("Valid priority range for SCHED_IDLE: %d - %d\n",
           sched_get_priority_min(SCHED_IDLE),
           sched_get_priority_max(SCHED_IDLE));
    printf("Valid priority range for SCHED_DEADLINE: %d - %d\n",
           sched_get_priority_min(SCHED_DEADLINE),
           sched_get_priority_max(SCHED_DEADLINE));
    printf("Valid priority range for SCHED_BATCH: %d - %d\n",
           sched_get_priority_min(SCHED_BATCH),
           sched_get_priority_max(SCHED_BATCH));


    if(argc != 3){
        printf("Wrong number of parameters.\nPlease enter policy and priority.");
        exit(-1);
    }

    printf("Before the change: use chrt -p pid at another terminal to see current policy and priority");
    getchar();
    int policy = atoi(argv[1]);
    struct sched_param sp;
    sp.sched_priority= atoi(argv[2]);;
    int check =  sched_setscheduler(0,policy,&sp);
    switch (check) {
        case 0:
            printf("Sucsess\n");
            break;
        case -1:
            printf("failed\n");
            break;
    }

    printf("After the change: use chrt -p pid at another terminal to see current policy and priority\n");
    int a=0;
    while(!a){scanf("%d",&a);}
    return 0;
}
