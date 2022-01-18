/*	======================================================================
	File Name: ThreadRace.c
	Purpose: To see the effect of multiple threads on shared resource.
	----------------------------------------------------------------------
	A. How to Run: 
		At terminal, type
		$ gcc ThreadRace.c -o ThreadRace -pthread
		$ ./ThreadRace

	B. Investigation:
		a. Run the process many times to see inconsistent/unexpected output. 
		b. Check how frequent context switching occurs.
		c. Check whether all threads can get chance to finish loop completely.
 	---------------------------------------------------------------------- 
	Sangeeta Biswas
	Assistant Professor,
	Dept. of CSE, University of Rajshahi,
	Rajshahi-6205, Bangladesh.
	sangeeta.cse@ru.ac.bd
   	---------------------------------------------------------------------- 
	20/8/2021
	======================================================================
*/

#include <pthread.h> 
#include <stdio.h>

int x = 100;

void sum(){
	int i;
	for (i = 1; i < 10; i++){
		printf("%d. Before Sum: %d\n", i, x);
		x = x + 1;
		printf("%d. After Sum: %d\n", i, x);
	}
}

void sub(){
	int i;
	for (i = 1; i < 10; i++){	
		printf("%d. Before Sub: %d\n", i, x);
		x = x - 1;
		printf("%d. After Sub: %d\n", i, x);
	}
}


int main(){
	int i;
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, (void *) sum, NULL);
	pthread_create(&tid2, NULL, (void *) sub, NULL);

	for (i = 1; i < 10; i++)
		printf("%d. Main thread-x: %d\n", i, x);

	return 0;
}
