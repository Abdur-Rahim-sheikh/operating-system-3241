// ftok() shmget()
// 5.9.2021

#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>

int main(){
	key_t key;
	int shmID;
	
	/*
		key_t ftok(const char *path, int id);
		
		a)	'path' must refer to an existing, accessible file.
		b)	'id' must be nonzero.	
		
		The ftok() function does not guarantee unique key generation. The key is created by 
		combining:
			a)	the given id byte, i.e., 8 bits,
			b)	the lower 16 bits of the inode number,
			c)	the lower 8 bits of the device number into a 32-bit result. 
		The occurrence of key duplication is very rare. 
	*/
	key = ftok("Semaphore_Processes.c", 'a');
	printf("Key: %d\n", key);
	
	/*
		int shmget(key_t key, size_t size, int shmflg);
		
		a)	a non-negative number.
			
		b)	'size' equal to the value of size rounded up to a multiple of PAGE_SIZE.
	
		c)	shmflg: IPC_CREAT  for creating a new segment.  If this flag is not used, 
			then shmget() will find the segment associated with key and check to see 
			if the user has permission to access the segment.
	*/	
	
	shmID = shmget(key, 1024, IPC_CREAT | 0666);
	printf("ShmID: %d\n", shmID);

	return 0;
}
