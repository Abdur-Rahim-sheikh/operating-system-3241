#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sched.h>
#include<wait.h>
#include<semaphore.h>
#include<sys/shm.h>
char lock[20]="/LastLock";
int main(){
    pid_t pid,ppid,cpid;
    
    cpid = fork();
    if(cpid==0){
        execlp("./Nebula","Nebula",NULL);
        
    }
    cpid = fork();
    if(cpid == 0){
        execlp("./Blackhole","Blackhole",NULL);
    }
    sem_t *sem = sem_open(lock, O_CREAT, 0666,1);
    sem_wait(sem);
    long cpuN = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t mask;
    sched_getaffinity(0,sizeof(cpu_set_t), &mask);
    for(int i=0;i<10;i++){
        printf("Galaxy:\nPid: %d, cpu: %d, scheduling_algorithm: %d\n",getpid(),sched_getcpu(),sched_getscheduler(0));
        for(int j=0;j<cpuN;j++){
            printf("%d ",CPU_ISSET(j,&mask));
        }
        printf("\n");
    }
    sem_post(sem);
    shmdt(sem);
    
    wait(NULL);
    return 0;
}