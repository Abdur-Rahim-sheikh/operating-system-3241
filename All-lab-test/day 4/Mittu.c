#define _GNU_SOURCE
#include<stdio.h>
#include<sched.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<string.h>
#include<wait.h>
#include<stdlib.h>
#include<semaphore.h>

int getshmid(){
    key_t key;
    key = ftok("helper.c",'a');

    return shmget(key,1024,IPC_CREAT | 0666);
}
int main(int argc,char * argv[]){
    pid_t pid;
    int a,b,result;
    
    
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    
    sem_t *sem = sem_open("/loc", O_CREAT, 0666,1);
    sem_wait(sem);
    printf("Mittu before:\npid: %d\nCPU: %d\na=%d, b=%d\n",getpid(),sched_getcpu(),a,b);
    

    int shmid = getshmid();
    char *res = shmat(shmid,NULL,0);
    result = atoi(res);
    result += a * b;
    printf("Mittu result: %d\n\n",result);
    sprintf(res,"%d",result);
    sem_post(sem);
    shmdt(sem);
    shmdt(res);
    
    return 0;
}