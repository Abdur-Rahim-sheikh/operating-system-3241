// 5.8.2021

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
	pid_t cpid, pid, i;

	cpid = fork(); // Create a child process. Return value: -Negative_Value / 0 / CHILD_PID

	if (cpid < 0){ // Execute by parent process for failure case.
		printf("Unsuccessfull(:");
		exit(-1);
	}
	else if (cpid == 0){ // Execute by child process.
		for (i = 0; i < 1; i--){
			pid = getpid();
			printf("I am child process-%u\n", pid);
		}
	}
	else if(cpid > 0){ // Execute by parent process.
		//for (i = 0; i < 1; i--){
			int *wstatus;
			pid = getpid();
			printf("I am parent process-%u, my child process: %u\n", pid, cpid);
			// wait(wstatus);
		//}
		
	}

	return 0;
}
