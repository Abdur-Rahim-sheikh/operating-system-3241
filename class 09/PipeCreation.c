// 17.8.2021
// Permission Value
//			User	Group	Other
//	r: 100 (4)	4	4	4
//	w: 010 (2)	2	2	2
//	x: 001 (1)	0	0	0
//		=============================
//				6	6	6

// Since pipe is a special type of file which is used for the reading and writing purpose,
// we do not need to give execution power to anyone.

// pipe() is used for creating an unnamed pipe, while mkfifo() is used for creating a named pipe. 
// Unnamed pipe can be used by associated processeses, i.e., processeses which have parent-child relationship/ who are siblings, i.e., having same parent.
// Named pipe can be used by unrelated processeses as a regular file. However, there is a difference between a regular file and named pipe.
// It does not have any contents on the filesystem.

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char *pipePath;
	int pipeFlag, fd;

	// Create a named pipe
	pipePath = "1stPipe";
	if(access(pipePath, F_OK) == 0) { // Pipe exists
		printf("%s is already created, so new pipe will not be created\n. ", pipePath);
	} 
	
	else {// Pipe does not exists, so we can create a new pipe.
		pipeFlag = mkfifo(pipePath, 0666); // mkfifo(pipePath, permission)
		if (pipeFlag < 0){
			printf("Error in creating a named pipe.\n");
			exit(-1);	
		} 
		else{
			printf("Pipe has been created successfully.\n");
		}
	}
	
	return 0;
}

