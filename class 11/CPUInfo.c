#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <sys/syscall.h>
#include <unistd.h>

void thread1(){
	int i, cpuNo;
	pid_t pid, tid;
	
	pid = getpid();
	tid = syscall(SYS_gettid);

	for (i = 0; i < 10; i++){
		cpuNo = sched_getcpu();
		printf("Thread1 (PID: %d, TID: %d) is running in CPU-%d\n", pid, tid, cpuNo);
	}
}

void thread2(){
	int i, cpuNo;
	pid_t pid, tid;
	
	pid = getpid();
	tid = syscall(SYS_gettid);

	for (i = 0; i < 10; i++){
		cpuNo = sched_getcpu();
		printf("Thread2 (PID: %d, TID: %d) is running in CPU-%d\n", pid, tid, cpuNo);
	}
}


int main(){
	pthread_t tid1, tid2;
	int i, cpuNo;
	pid_t pid, tid, cpid;

	cpid = fork();

	if (cpid == 0){ // Child process
		pid = getpid();
		tid = syscall(SYS_gettid);

		for (i = 0; i < 10; i++){
			cpuNo = sched_getcpu();
			printf("Main thread of Child (PID: %d, TID: %d) is running in CPU-%d\n", pid, tid, cpuNo);
		}
	}
	else if (cpid > 0){ // Parent process
		pid = getpid();
		tid = syscall(SYS_gettid);

		pthread_create(&tid1, NULL, (void *) thread1, NULL);
		pthread_create(&tid2, NULL, (void *) thread2, NULL);

		for (i = 0; i < 10; i++){
			cpuNo = sched_getcpu();
			printf("Main thread of Parent (PID: %d, TID: %d) is running in CPU-%d\n", pid, tid, cpuNo);
		}
		
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);

	}

	return 0;
}
