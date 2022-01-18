/* 	Semaphore is a simple integer value. It is used for managing concurrent threads and processes.
	It was proposed by Dijkstra in 1965.
	
	Here we will see how we can use 'Semaphore' for handling concurrent threads.
	
	14.9.2019
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>

int x = 10;
sem_t key;

void sum_thread(){
	sem_wait(&key);
	
	printf("x = %d in Sum_Thread [CPU: %d]: Before Operation\n", x, sched_getcpu());
	x = x + 1;
	printf("x = %d in Sum_Thread [CPU: %d]: After Operation\n", x, sched_getcpu());
	
	sem_post(&key);
}

void sub_thread(){
	sem_wait(&key);
	
	printf("x = %d in Sub_Thread [CPU: %d]: Before Operation\n", x, sched_getcpu());
	x = x - 1;
	printf("x = %d in Sub_Thread [CPU: %d]: After Operation\n", x, sched_getcpu());
	
	sem_post(&key);
}

int main(){
	pthread_t TID1, TID2;
	
	sem_init(&key, 0, 1);
	
	// Create two threads.
	pthread_create(&TID1, NULL, (void*) sum_thread, NULL);
	pthread_create(&TID2, NULL, (void*) sub_thread, NULL);
	
	sem_wait(&key);
	printf("x = %d in MainThread [CPU: %d]\n", x, sched_getcpu());
	sem_post(&key);	
	
	// Wait for other threads to be finished.
	pthread_join(TID1, NULL);
	pthread_join(TID2, NULL);
		
	return 0;
}
