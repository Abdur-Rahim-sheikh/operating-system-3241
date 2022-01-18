/*	======================================================================
	File Name: ThreadRace_Mutex.c
	Purpose: To create an environment where multiple threads can share
	resources smoothly.
	----------------------------------------------------------------------
	Notes: 
	A. At terminal, type
		$ gcc ThreadRace_Mutex.c -o ThreadRace_Mutex -pthread
		$ ./ThreadRace_Mutex

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
	21/8/2021
	======================================================================
*/

#include <pthread.h> 
#include <stdio.h>

int x = 100;
pthread_mutex_t key;

void sum(){
	int i;
	for (i = 1; i < 10; i++){
		pthread_mutex_lock(&key); // Lock the critical section so that other threads cannot enter.

		printf("%d. Before Sum: %d\n", i, x);
		x = x + 1;
		printf("%d. After Sum: %d\n", i, x); // Unlock the critical section so that other threads can enter.

		pthread_mutex_unlock(&key);
	}
}

void sub(){
	int i;
	for (i = 1; i < 10; i++){
		pthread_mutex_lock(&key);

		printf("%d. Before Sub: %d\n", i, x);
		x = x - 1;
		printf("%d. After Sub: %d\n", i, x);

		pthread_mutex_unlock(&key);
	}
}


int main(){
	int i;
	pthread_t tid1, tid2;

	// Create two threads.
	pthread_create(&tid1, NULL, (void *) sum, NULL);
	pthread_create(&tid2, NULL, (void *) sub, NULL);

	for (i = 1; i < 10; i++){
		pthread_mutex_lock(&key);
		printf("%d. Main thread: %d\n", i, x);
		pthread_mutex_unlock(&key);
	}

	// Main thread will wait until sub-threads are running.
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
