#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char * argv[]){
    pid_t pid,ppid,cpid;
    
    char pipe[100]= "./";
    if(argc==1 || access(argv[1],F_OK)!=0){
        printf("no pipe given or exists in that name.\n");
        exit(-1);
    }
    strcat(pipe,argv[1]);
    
    int id = open(pipe,O_RDWR);
    char inputs[200];
    read(id,inputs,sizeof(inputs));
    printf("from Minu: %s\n",inputs);
    printf("Minu also sent:\n");
    while(1){
        read(id,inputs,sizeof(inputs));
        printf("%s\n",inputs);
        if(strcmp(inputs,"Bye")==0) break;
    }

    write(id,"Bye",4);
    close(id);
    return 0;
}