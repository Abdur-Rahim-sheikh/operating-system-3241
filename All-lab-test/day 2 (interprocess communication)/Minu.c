#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
void addWord(char *tem, char *word){
    strcat(tem," ");
    strcat(tem,word);
}

int main(int argc, char * argv[]){
    pid_t pid;
    char tem[100],msg[500];
    char pipe[100]= "./";
    if(argc==1 || access(argv[1],F_OK)!=0){
        printf("no pipe given or exists in that name.\n");
        exit(-1);
    }
    strcat(pipe,argv[1]);
    printf("pipe given: %s\n",pipe);
    
    int id = open(pipe,O_RDWR);

    // sending pid,ppid,Hello
    sprintf(msg, "%d", getpid());
    sprintf(tem, "%d", getppid());

    addWord(msg,tem);
    addWord(msg,"Hello");
    write(id,msg,strlen(msg)+1);

    while(1){
        scanf("%[^\n]%*c",tem);
        // scanf("%s",tem);
        write(id,tem,strlen(tem)+1);
        if(strcmp(tem,"Bye")==0)break;
    }

    read(id,msg,sizeof(msg));
    printf("Binu said: %s\n",msg);
    
    close(id);
    return 0;
}