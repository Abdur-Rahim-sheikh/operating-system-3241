// Write to a SystemV message queue.

#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msgbuf{
	long msgType; // Be Careful!!! Data type should be a long integer. 
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

	//  Get a SystemV message queue identifier.
	msqID = create_msgQ("/home/cse/OperatingSystem/ClassCode/Process_Semaphore"); 
	
	// Prepare data to be sent.
	msg.msgType = 1;
	strcpy(msg.buffer, "Operating System\n");
	
	/*	Write to the message queue.
		int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
	*/
	msgSz = sizeof(msg) - sizeof(long int);
	msgsnd(msqID, &msg, msgSz, 0);
	
	return 0;
}

