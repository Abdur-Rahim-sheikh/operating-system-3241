#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <sys/syscall.h>
#include <signal.h>
#include <stdlib.h>
int result;
pthread_mutex_t key;

struct parameter{
    int a, b;
}pam;

void Ittu(void *pam){
    struct parameter *p = (struct parameter *) pam;

    pthread_mutex_lock(&key);
    result = p->a + p->b;
    printf("PID: %u, TID: %ld, CPU: %d, result: %d\n",getpid(),syscall(SYS_gettid),sched_getcpu(),result);
    if(result == 100)kill(getpid(),SIGTERM);
    pthread_mutex_unlock(&key);
}

void Bittu(void *pam){
    struct parameter *p = (struct parameter *) pam;

    pthread_mutex_lock(&key);
    result = p->a - p->b;
    printf("PID: %u, TID: %ld, CPU: %d, result: %d\n",getpid(),syscall(SYS_gettid),sched_getcpu(),result);
    if(result == 100)kill(getpid(),SIGTERM);
    pthread_mutex_unlock(&key);
}

void Mittu(void *pam){
    struct parameter *p = (struct parameter *) pam;

    pthread_mutex_lock(&key);
    result = p->a * p->b;
    printf("PID: %u, TID: %ld, CPU: %d, result: %d\n",getpid(),syscall(SYS_gettid),sched_getcpu(),result);
    if(result == 100)kill(getpid(),SIGTERM);
    pthread_mutex_unlock(&key);
}

void signal_handler(int c){
    pthread_mutex_lock(&key);
    printf("main Thread:I am forced to terminate by my thread after getting 100.\n");
    exit(-1);
    pthread_mutex_unlock(&key);
}

int main(){
    int a,b;
    
    pthread_t tid1,tid2,tid3;
    scanf("%d %d",&a,&b);
    // struct parameter pam;
    pam.a = a;
    pam.b = b;
    signal(SIGTERM,signal_handler);
    for(int i=0;i<10;i++){
        printf("Calling %d'th time\n",i);
        pthread_create(&tid1,NULL,(void *) Ittu, (void *)&pam);
        pthread_create(&tid2,NULL,(void *) Bittu,(void *)&pam);
        pthread_create(&tid3,NULL,(void *) Mittu,(void *)&pam);
    }
    

    
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    
    
    return 0;
}