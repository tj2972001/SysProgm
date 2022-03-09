#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    printf("In main\n");
    int fd1[2], fd2[2];
    int pipeStatus1, pipeStatus2;
    char msg[2][20] = {"Tejas", "jadhav"};
    char buffer[20];
    if(pipe(fd1)==-1){
        perror("Failed to create pipe1 [FAIL...]");
        return 1;
    }
    if(pipe(fd2)==-1){
        perror("Failed to create pipe2 [FAIL...]");
        return 1;
    }
    int id = fork();
    if(id==-1){
        perror("Failed to create child process [FAIL...]\n");
        return 1;
    }
    if(id==0){
        // Child process
        printf("Child process\n");
        close(fd1[1]);  // Close write end of pipe1
        close(fd2[0]);  // Close read end of pipe2
        printf("Writing [%s] to pipe2\n",msg[0]);
        write(fd2[1],msg[0],sizeof(msg[0]));
        printf("Reading from pipe1\n");
        read(fd1[0],buffer,sizeof(buffer));
        printf("read [%s] from pipe1\n",buffer);
        close(fd1[0]); // Read complete from pipe1. Close read end of pipe1.
        close(fd2[1]); // Write complete to pipe2. Close write end of pipe2.
    }else{
        // Parent process
        printf("Parent process\n");
        close(fd1[0]); // Close read end of pipe1
        close(fd2[1]); // Close write end of pipe2
        printf("Writing [%s] to pipe1\n",msg[1]);
        write(fd1[1],msg[1],sizeof(msg[1]));
        printf("Reading from pipe2\n");
        read(fd2[0], buffer, sizeof(buffer));
        printf("Read [%s] from pipe2\n",buffer);
        close(fd1[1]); // Write complete to pipe1. Close write end of pipe1
        close(fd2[0]); // Read complete from pipe2. Close read end of pipe2 
    }
    printf("Returning from main\n");
    return 0;
}