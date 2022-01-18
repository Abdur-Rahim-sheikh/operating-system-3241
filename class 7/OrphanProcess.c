// Parent process will terminate before the child process. Therfore, child process will become an orphan.
// OS process 'systemd' will become the parent of the orphan process.
// We will not be able to terminate child process by sending signal externally.

// Will 'systemd' kill this orphan process after some time.
// If it happens, please check how long your OS will take to kill the orphan process.

// 9.8.2021

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
	pid_t childPID, pid, parentPID;
	int i;

	childPID = fork(); // Create a child process. Return value: -Negative_Value / 0 / CHILD_PID

	if (childPID == -1){ // Execute by parent process for failure case.
		printf("Unsuccessfull(:");
		exit(-1);
	}
	else if (childPID == 0){ // Execute by the child process.
		pid = getpid();
		parentPID = getppid();
		for (i = 0; i < 1; i--){
			printf("I am child process-%u. My parent process-%u\n", pid, parentPID);
		}
	}
	else if(childPID > 0){ // Execute by the parent process.
		for (i = 0; i < 100000; i++){ // This loop will help us to see the switching of parent process.
			pid = getpid();
			printf("I am parent process-%u, my child process: %u\n", pid, childPID);
		}
		sleep(5);
	}

	return 0;
}
