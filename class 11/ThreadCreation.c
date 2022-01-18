/*	======================================================================
	File Name: ThreadCreation.c
	Purpose: To create multiple threads.
	----------------------------------------------------------------------
	Notes: 
	A. At one terminal, type
		$ gcc ThreadCreation.c -o ThreadCreation -pthread
		$ ./ThreadCreation

	B. At another terminal, type
		$ pstree
		
		** We will be able to see a process named 'ThreadCreation' with two threads inside curly brackets.
		├─gnome-terminal-─┬─bash───ThreadCreation───2*[{ThreadCreation}]

		$ pstree -p
		├─gnome-terminal-(2026)─┬─bash(2035)───ThreadCreation(14682)─┬─{ThreadCreation}(14683)
                             		                                     └─{ThreadCreation}(14684)

	C. Depending on the speed of our computer, we need to decide the termination value so that we can get time
	   to see the process_tree.

	D. If we forget to write -pthread, we would get an error message similar to the following error message.

		$ gcc ThreadCreation.c -o ThreadCreation 
		/tmp/cceFx1jH.o: In function `main':
		ThreadCreation.c:(.text+0x78): undefined reference to `pthread_create'
		ThreadCreation.c:(.text+0xb4): undefined reference to `pthread_create'
		collect2: error: ld returned 1 exit status

	----------------------------------------------------------------------
	To create a new thread: 
		int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *),  void *arg);

	Simple form:
		int pthread_create(pthread_t *thread, NULL, (void *) thread_function, NULL);
 	---------------------------------------------------------------------- 
	Sangeeta Biswas
	Assistant Professor,
	Dept. of CSE, University of Rajshahi,
	Rajshahi-6205, Bangladesh.
	sangeeta.cse@ru.ac.bd
   	---------------------------------------------------------------------- 
	19/8/2021
	======================================================================
*/

#include <stdio.h>
#include <pthread.h>

void sub_thread1(){
	int i;

	for (i = 1; i < 1000000; i++)
		printf("%d. Sub Thread1\n", i);	
}

void sub_thread2(){
	int i;

	for (i = 1; i < 1000000; i++)
		printf("%d. Sub Thread2\n", i);	
}

int main(){
	int i;
	pthread_t threadID1, threadID2;

	pthread_create(&threadID1, NULL, (void *) sub_thread1, NULL);
	pthread_create(&threadID2, NULL, (void *) sub_thread2, NULL);

	for (i = 1; i < 1000000; i++)
		printf("%d. Main Thread\n", i);

	return 0;
}
