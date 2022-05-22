#define _GNU_SOURCE
#include<unistd.h>
#include<sched.h>
#include<stdlib.h>
#include<stdio.h>
int main(){
    pid_t cpid1,cpid2,pid,ppid;

    cpid1 = fork();

    if(cpid1==0){
        execlp("./Pillow","Pillow",NULL);
    }
    
    cpid2 = fork();

    if(cpid2 == 0){
        execlp("./Killow","Killow",NULL);
    }
    if(cpid1 <0 || cpid2 < 0){
        printf("problem with creating child\n");
        exit(0);
    }
    
    if(cpid1>0 && cpid2>0){
        while(1){
            printf("Process-%u, parent of Pillow-%u and Killow-%u, running at CPU-%d.\n",getpid(),cpid1,cpid2,sched_getcpu());
            sleep(2);
        }
    }
    


    return 0;
}