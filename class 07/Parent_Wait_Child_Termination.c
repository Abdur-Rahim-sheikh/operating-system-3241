// 9.8.2021

#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
	pid_t childPID, pid, parentPID;

	childPID = fork();

	if (childPID < 0){
		exit(-1);
	}
	else if (childPID == 0){
		pid = getpid();
		parentPID = getppid();
		printf("I am child process-%u. My parent process-%u\n", pid, parentPID);	
		sleep(60);
		printf("WAke\n");
	}
	else if (childPID > 1){
		pid = getpid();
		printf("I am parent process-%u. My child process-%u\n", pid, childPID);
		// wait(NULL); // Parent process will wait for the termination of the child process.

	}

	return 0;
}
