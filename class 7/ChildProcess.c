// 9.8.2021

#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid;

	pid = getpid();
	printf("I am child-%u.\n", pid);
	sleep(20);
	return 0;
}
