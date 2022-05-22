#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>


int main(int argc, char* argv[]){
    for(int i=1;i<argc;i++){
        if(access(argv[i],F_OK)==0){
            printf("Skipping as %s pipe already exists.\n",argv[i]);
        }
        else{
            int status = mkfifo(argv[i],0666);
            
            if(status==-1) printf("Error creating %s\n",argv[i]);
            else printf("%s pipe is created\n",argv[i]);
        }
    }
    return 0;
}