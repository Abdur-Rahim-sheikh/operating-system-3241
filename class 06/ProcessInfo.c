// 5.8.2021

#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid, ppid;
	int i;

	for (i = 0; i < 1; i--){
		pid = getpid();
		ppid = getppid();

		printf("My PID: %u\n", pid);
		printf("My Parent's PID: %u\n", ppid);

	}

	return 0;
}
