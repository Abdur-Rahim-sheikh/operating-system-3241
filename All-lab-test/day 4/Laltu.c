#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<string.h>
#include<wait.h>
#include<semaphore.h>

int getshmid(){
    key_t key;
    key = ftok("helper.c",'a');

    return shmget(key,1024,IPC_CREAT | 0666);
}
int main(){
    pid_t pid,cpid[3];
    int a,b;

    scanf("%d %d",&a,&b);
    char astr[20],bstr[20];
    sprintf(astr,"%d",a);
    sprintf(bstr,"%d",b);
    
    int shmid = getshmid();
    char *res = shmat(shmid,NULL,0);
    sprintf(res,"%d",0);
    shmdt(res);

    
    cpid[0] = fork();
    if(cpid[0]==0){
        execlp("./Ittu","Ittu",astr,bstr,NULL);
    }
    
    cpid[1] = fork();
    if(cpid[1]==0){
        execlp("./Bittu","Bittu",astr,bstr,NULL);
    }

    cpid[2] = fork();
    if(cpid[2]==0){
        execlp("./Mittu","Mittu",astr,bstr,NULL);
    }
    
    
    wait(NULL);
    return 0;
}