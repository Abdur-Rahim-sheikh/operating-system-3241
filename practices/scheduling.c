#define _GNU_SOURCE

#include<stdio.h>
#include<sched.h>

int main(){
    int policy;

    struct sched_param param;

    policy = sched_getscheduler(0);
    printf("Scheduling Policy: %d\n",policy);
    printf("%d %d %d\n",SCHED_OTHER,SCHED_BATCH,SCHED_IDLE);
    param.sched_priority = 34;
    sched_setscheduler(0,&param);
    

    policy = sched_getscheduler(0);
    printf("Scheduling policy: %d\n",policy);
    
    return 0;
}