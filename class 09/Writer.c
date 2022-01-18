// 17.8.2021
// To write to a named pipe.

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include<stdio.h>
int main(){
	int fd;
	char *pipePath;
	char *msg;

	pipePath = "./1stPipe";
	msg = "Hello\n";
	
	fd = open(pipePath, O_WRONLY);	
	printf("Writting: %s\n",msg);
	write(fd, msg, strlen(msg) + 1);
	close(fd);

	return 0;
}


