#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
int main(){
    printf("hello from main\n");
    int fd[2];
    char msg[2][20]={"Tejas","Jadhav"};
    char buffer[20];
    int status = pipe(fd);
    int id = fork();
    if(id==-1){
        printf("Fork failed\n");
        return 1;
    }
    if(id==0){
        // Child process
        printf("Child process\t pid: [%d]\t fds: [%d] and [%d]\n",getpid(),fd[0],fd[1]);
        close(fd[0]);
        printf("writing msg1: %s\n",msg[0]);
        write(fd[1],msg[0],sizeof(msg[0]));
        printf("writing msg2: %s\n",msg[1]);
        write(fd[1],msg[1],sizeof(msg[1]));
        close(fd[1]);
    }else{
        // Parent process
        printf("Parent process\t pid: [%d]\t fds: [%d] and [%d]\n",getpid(),fd[0],fd[1]);
        wait(NULL);
        close(fd[1]);
        printf("Reading from pipe\n");
        read(fd[0],buffer,sizeof(buffer));
        printf("read [%s] from pipe\n",buffer);
        printf("Reading from pipe\n");
        read(fd[0],buffer,sizeof(buffer));
        printf("read [%s] from pipe\n",buffer);
        close(fd[0]);
    }
    return 0;
}