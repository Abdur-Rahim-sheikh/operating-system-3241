// 5.8.2021

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	pid_t cpid;
	cpid = fork(); // Create a child process. Return value: -Negative_Value / 0 / CHILD_PID

	printf("Hello %u Your child %u\n",getpid(),cpid);
	sleep(60);
	return 0;
}
