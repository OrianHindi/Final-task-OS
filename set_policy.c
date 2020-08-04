//
// Created by orian on 01/08/2020.
//

#define _GNU_SOURCE  /
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


int main(int argc , char* argv[]){

    printf("Program pid:%d\n",getpid());

    if(argc != 3){
        printf("Wrong number of parameters.\nPlease enter policy and priority.");
        exit(-1);
    }

    printf("Before the change: use chrt -p pid at another terminal to see current policy and priority\n");
    getchar();
    int policy = atoi(argv[1]);
    int priority = atoi(argv[2]);
    if(policy == SCHED_DEADLINE){
        struct sched_attr sa;
        sa.size=sizeof(sa);
        sa.sched_flags=0;
        sa.sched_nice=0;
        sa.sched_priority=priority;

        /* creates a 10ms/30ms reservation */
        sa.sched_policy= SCHED_DEADLINE;
        sa.sched_runtime=10*1000*1000;
        sa.sched_period = 30*1000*1000;
        sa.sched_deadline = 30*1000*1000;

        int check = sched_setattr(0,&sa, 0);
        switch (check) {
            case 0:
                printf("Sucsess , policy and priority is changed.\n");
                break;
            case -1:
                printf("Deadline failed,\n");
                break;
        }
    }
    else{
        struct sched_param sp;
        sp.sched_priority= priority;
        int check =  sched_setscheduler(0,policy,&sp);
        switch (check) {
            case 0:
                printf("Sucsess ,priority and policy has changed.\n");
                break;
            case -1:
                printf("failed\n");
                break;
        }

        printf("After the change: use chrt -p pid at another terminal to see current policy and priority\n");

    }

    int a=0;
    while(!a){scanf("%d",&a);}
    return 0;
}
