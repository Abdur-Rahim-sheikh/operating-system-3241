#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<string.h>
int create_shared_memory(){
    key_t key;
    int shmID;
    key = ftok("SharedMemory_Writer.c",'a');
    shmID = shmget(key,1024,IPC_CREAT | 0666);
    return shmID;
}

void write_to_shm(int x){
    int shmID = create_shared_memory();
    char *str = shmat(shmID,NULL,0);

    char num[100];
    sprintf(num,"%d",x);
    strcpy(str,num);
    
    shmdt(str);
}

void read_from_shm(){
    int shmID = create_shared_memory();
    char *str = shmat(shmID,NULL,0);
    printf("In read from: function: %s\n",str);
    shmdt(str);
}
int main(){
    pid_t pid,ppid,cpid;
    int i,j,k,n,m;
    int x = 10;
    write_to_shm(x);
    read_from_shm();

    cpid = fork();
    if(cpid==0){
        printf("%d before\n",x);
        x++;
        printf("%d after\n",x);
    }
    
    return 0;
}