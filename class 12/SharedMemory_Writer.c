// shmat(), shmdt()
// 5.9.2021

#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main(){ 
	int shmID = 327722;	// It should be the same number used in SharedMemory_Reader.c
				// Either we can decide this number or we can take help from ftok().	
				// Here we get this number by executing SharedMemory_Creation.c.
				
	// Attach shared memory with the ddress space of the process.
	char *str = shmat(shmID, NULL, 0);
	
	// Put data into the shared memory.
	strcpy(str, "Hello ALL BONDHURA\n");
	
	// Detach the shared memory segment.
	shmdt(str);
	
	return 0;
}
