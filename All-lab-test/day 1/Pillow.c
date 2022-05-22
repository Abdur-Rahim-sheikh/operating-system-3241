#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){
    pid_t pid,ppid,cpid;
    int i,j,k,n,m;
    
    while(1){
        printf("I am child - %u running at CPU - %d.\n",getpid(),sched_getcpu());
        sleep(2);
   }
    
    return 0;
}