#define _GNU_SOURCE

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<err.h>
#include<pwd.h>

void closePipe(int fd[]){
    close(fd[0]);
    close(fd[1]);
}

int main(){
    printf("hello from main\n");
    const int BUF_SIZE = 20;
    const int MSG_ARR_SIZE=2;
    int fd[2];
    char msg[MSG_ARR_SIZE][BUF_SIZE] = {"Tejas", "Jadhav"};
    char buffer[BUF_SIZE];
    memset(buffer,0,sizeof(buffer));
    if(pipe(fd) == -1){
        perror("Failed to create pipe [FAIL...]");
        return 1;
    }
    printf("fd[0] and fd[1] are [%d] and [%d]\n",fd[0],fd[1]);
    //printf("Default pipe reading end size in Bytes is [%d]\n", fcntl(fd[0], F_GETPIPE_SZ));
    struct stat statBuf;
    struct passwd *userDetail;
    int uid, gid;
    if (fstat(fd[1], &statBuf) == -1)
    {
        perror("Failed to get stat\n");
        closePipe(fd);
        return 1;
    }
    uid = statBuf.st_uid;
    gid = statBuf.st_gid;
    userDetail = getpwuid(uid);
    printf("-----------------Printing pipe read end stats:----------------------\n");
    printf("user_id and group_id are [%d] and [%d]\n", uid, gid);
    printf("username is [%s]\n", userDetail->pw_name);
    printf("file size is [%ld]\n", statBuf.st_size);
    printf("inode number is [%ld]\n", statBuf.st_ino);
    printf("Number of blocks allocated are [%ld] of size [%ld]\n", statBuf.st_blocks, statBuf.st_blksize);
    printf("Device type is [%lu]\n", statBuf.st_dev);
    printf("------------------------------------------------------------\n");
    printf("Writing to pipe\n");
    for(int i=0;i<MSG_ARR_SIZE;i++){
        int w = write(fd[1],msg[i],sizeof(msg[0]));
        if(w==-1){
            perror("Failed to write to pipe");
            closePipe(fd);
            return 1;
        }
        printf("Wrote [%d] Bytes to pipe\n",w);
    }
    close(fd[1]);

    /*

    int totalBytesWrote = 0;
    for(int i=0;i<70000;i++){
        char t = (char)((rand()%24))+97;
        // Write will block after pipe gets full
        int w = write(fd[1],&t,sizeof(char));
        if(w==-1){
            perror("Failed to write to pipe");
            closePipe(fd);
            return 1;
        }
        totalBytesWrote+=w;
        printf("Wrote [%c] ; Total: [%d] Bytes\n",t,totalBytesWrote);
    }
    
    int offt;
    if(offt = lseek(fd[1],10,SEEK_CUR) && offt!=-1){
        perror("Failed to change offset");
        closePipe(fd);
        return 1;
    }
    printf("Current offset is [%d]\n",offt);
    
    */

    printf("Reading from pipe\n");
    for(int i=0;i<MSG_ARR_SIZE;i++){
        int r = read(fd[0],buffer,sizeof(buffer));
        if(r==-1){
            perror("Pipe read failed\n");
            closePipe(fd);
            return 1;
        }
        printf("Read [%d] bytes from pipe: [%s]\n",r,buffer);
    }
    close(fd[0]); // close read fd
    return 0;
}