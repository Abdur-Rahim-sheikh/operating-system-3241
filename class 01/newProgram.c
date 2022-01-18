#include<stdio.h>
#include<unistd.h>

int main(){

    pid_t pid;

    pid = getpid();
    printf("%u\n",pid);
    return 0;
}