#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
    pid_t pid,ppid,cpid,kpid;
    int i,j,k,n,m;
    
    cpid = fork();
    kpid = fork();
    pid = getpid();
    for(i=0;i<1;i--)
    printf("My pid %d -->%d --> %d\n",pid,cpid,kpid);
    
    
    return 0;
}