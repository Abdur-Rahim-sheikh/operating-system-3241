#include <pthread.h> 
#include <stdio.h>

int x = 100;
pthread_mutex_t key;
void sum(){
	int i;
	for (i = 1; i < 10; i++){
        pthread_mutex_lock(&key);
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

	pthread_create(&tid1, NULL, (void *) sum, NULL);
	pthread_create(&tid2, NULL, (void *) sub, NULL);

	for (i = 1; i < 10; i++){
		printf("%d. Main thread: %d\n", i, x);
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
