// 17.8.2021
// To read from a named pipe.

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include<stdio.h>
int main(){
	int fd;
	char *pipePath;
	char buffer[200];

	pipePath = "./1stPipe";
	fd = open(pipePath, O_RDONLY);	
	read(fd, buffer, sizeof(buffer));
	close(fd);

	// Display to the monitor.
	// write(STDOUT_FILENO, buffer, strlen(buffer));
	printf("%s\n",buffer);
	return 0;
}
