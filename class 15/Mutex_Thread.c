/* 	Here we will see how we can use 'Mutex' for handling concurrent threads.
	
	14.9.2019
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>

int x = 10;
pthread_mutex_t key;

void sum_thread(){
	pthread_mutex_lock(&key);
	printf("x = %d in Sum_Thread [CPU: %d]: Before Operation\n", x, sched_getcpu());
	x = x + 1;
	printf("x = %d in Sum_Thread [CPU: %d]: After Operation\n", x, sched_getcpu());
	pthread_mutex_unlock(&key);
}

void sub_thread(){
	pthread_mutex_lock(&key);
	printf("x = %d in Sub_Thread [CPU: %d]: Before Operation\n", x, sched_getcpu());
	x = x - 1;
	printf("x = %d in Sub_Thread [CPU: %d]: After Operation\n", x, sched_getcpu());
	pthread_mutex_unlock(&key);
}

int main(){
	int cpuNo;
	pthread_t TID1, TID2;
	
	pthread_create(&TID1, NULL, (void*) sum_thread, NULL);
	pthread_create(&TID2, NULL, (void*) sub_thread, NULL);
	
	pthread_mutex_lock(&key);
	printf("x = %d in MainThread [CPU: %d]\n", x, sched_getcpu());
	pthread_mutex_unlock(&key);	
	
	pthread_join(TID1, NULL);
	pthread_join(TID2, NULL);
		
	return 0;
}
