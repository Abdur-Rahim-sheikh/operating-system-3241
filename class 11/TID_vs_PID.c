/*	======================================================================
	File Name: TID_vs_PID.c
	Purpose: To create an environment where multiple threads can share
	resources smoothly.
	----------------------------------------------------------------------
	Notes: 
	A. At terminal, type
		$ gcc TID_vs_PID.c -o TID_vs_PID -pthread
		$ ./TID_vs_PID

	B. Run process many times to ensure there is no inconsistent/unexpected 
	   output. 

	C. Check what is the effect of pthread_join().
 	---------------------------------------------------------------------- 
	Sangeeta Biswas
	Assistant Professor,
	Dept. of CSE, University of Rajshahi,
	Rajshahi-6205, Bangladesh.
	sangeeta.cse@ru.ac.bd
   	---------------------------------------------------------------------- 
	22/8/2021
	======================================================================
*/

#include <pthread.h> 
#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

void sub_thread1(){
	int i;
	pid_t pid, tid;
	for (i = 1; i < 10; i++){
		pid = getpid();
		tid = syscall(SYS_gettid);
		printf("%d. SubThread1\n", i); 
	}
}

void sub_thread2(){
	pid_t pid, tid;
	for (int i = 1; i < 10; i++){
		pid = getpid();
		tid = syscall(SYS_gettid);
		printf("%d. SubThread1\n", i); 
	}
}


int main(){
	int i;
	pthread_t tid1, tid2;
	pid_t pid, tid;

	// Create two threads.
	pthread_create(&tid1, NULL, (void *) sub_thread1, NULL);
	pthread_create(&tid2, NULL, (void *) sub_thread2, NULL);

	for (i = 1; i < 10; i++){
		pid = getpid();
		tid = syscall(SYS_gettid);
		printf("%d. MainThread1\n", i); 
	}

	// Main thread will wait until sub-threads are running.
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
