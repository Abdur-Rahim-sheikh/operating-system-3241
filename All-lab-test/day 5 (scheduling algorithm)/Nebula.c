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
#include<pthread.h>
#include<stdlib.h>
char lock[20]="/LastLock";
void x(){
    sem_t *sem = sem_open(lock, O_CREAT, 0666,1);
    sem_wait(sem);
    long cpuN = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t mask;
   
    pthread_getaffinity_np(pthread_self(),sizeof(cpu_set_t),&mask);
    
    //proving mask really got set
    pthread_getaffinity_np(pthread_self(),sizeof(cpu_set_t),&mask);
    
    printf("Nebula (x,%d)=> Pid: %d cpu: %d, scheduling_algorithm: %d\n",gettid(),getpid(),sched_getcpu(),sched_getscheduler(0));
    for(int j=0;j<cpuN;j++){
        printf("%d ",CPU_ISSET(j,&mask));
    }
    printf("\n");
    sem_post(sem);
    shmdt(sem);
    
}

void y(){
    long cpuN = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t mask;

    sem_t *sem = sem_open(lock, O_CREAT, 0666,1);
    sem_wait(sem);
    
    pthread_getaffinity_np(pthread_self(),sizeof(cpu_set_t), &mask);

  
    printf("Nebula (y,%d)=> Pid: %d, cpu: %d, scheduling_algorithm: %d\n",gettid(),getpid(),sched_getcpu(),sched_getscheduler(0));
    for(int j=0;j<cpuN;j++){
        printf("%d ",CPU_ISSET(j,&mask));
    }
    printf("\n");

    sem_post(sem);
    shmdt(sem);

    
}
int main(){
    int iterate = 100;
    pthread_t tid1,tid2;

    struct sched_param prio;
    prio.sched_priority = 30;
    int permission = sched_setscheduler(0,SCHED_RR,&prio);

    if(permission==-1){
        printf("Permission denied in Nebula for sched_setscheduler\n");
        printf("Please run the main process with root permission after all compilation\nsudo ./Galaxy\n");
        exit(-1);
    }
    for(int i=0;i<iterate;i++){
        printf("%d'th time calling:\n",i+1);
        pthread_create(&tid1,NULL,(void *)x,NULL);
        pthread_create(&tid2,NULL,(void *)y,NULL);

    }
    
    long cpuN = sysconf(_SC_NPROCESSORS_ONLN);
    cpu_set_t mask;
    sched_getaffinity(0,sizeof(cpu_set_t), &mask);
    sem_t *sem = sem_open(lock, O_CREAT, 0666,1);
    sem_wait(sem);
    for(int i=0;i<10;i++){
        printf("Nebula:\nPid: %d, cpu: %d, scheduling_algorithm: %d\n",getpid(),sched_getcpu(),sched_getscheduler(0));
        for(int j=0;j<cpuN;j++){
            printf("%d ",CPU_ISSET(j,&mask));
        }
        printf("\n");
    }
    sem_post(sem);
    shmdt(sem);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    
    return 0;
}