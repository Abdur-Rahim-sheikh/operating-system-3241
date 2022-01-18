// Read from a SystemV message queue.

#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msgbuf{
	long msgType; // Be Careful!!! Data type should be a long integer. Wrong data type (e.g., int) can block the process.
	char buffer[100];
}msg;

int create_msgQ(char *path){
	key_t key;
	int msqID;
	
	key = ftok(path, 'a');
	msqID = msgget(key, IPC_CREAT| 0666);
	
	printf("Key: %d\n", key);
	printf("MSQID: %d\n", msqID);
	
	return msqID;
}

int main(){
	int msqID;
	size_t msgSz;
	long int msgType;
	
	//  Get a SystemV message queue identifier.
	msqID = create_msgQ("/home/cse/OperatingSystem/ClassCode/Process_Semaphore"); 
	
	/* 	Read from the message queue.
		ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
	
	*/
	msgSz = sizeof(msg) - sizeof(long int);
  	msgType = 1; // The message type should be the same as the Writer uses.
	msgrcv(msqID, &msg, msgSz, msgType, 0);  
	printf("Recieved Message: %s\n", msg.buffer);
	
	return 0;
}

