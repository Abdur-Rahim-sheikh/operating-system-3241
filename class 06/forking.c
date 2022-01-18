#include<stdio.h>
#include<unistd.h>

int main(){
    
    fork();
    printf("Hi %u\n",getpid());

    fork();
    printf("Hey %u\n",getpid());
    
    fork();
    printf("Hello %u\n",getpid());
    
    return 0;
}