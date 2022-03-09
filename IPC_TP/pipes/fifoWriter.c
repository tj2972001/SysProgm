#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<time.h>

int main(){
    printf("In fifoWriter main\n");
    int arr[5]={0};
    srand(time(NULL));
    for (int i = 0; i < 5; i++){
        arr[i] = rand() % 100;
        printf("Generated [%d]\n",arr[i]);
    }
    //int fd = open("sum",O_NONBLOCK); /* Opening FIFO in Non-blocking mode doesnt block its execution */
    int fd = open("sum",O_WRONLY);
    if(fd==-1){
        perror("File open failed");
        return 1;
    }
    int totalBytesWrite = 0;
    for(int i=0;i<5;i++){
        int writeBytes = write(fd,&arr[i],sizeof(int));
        if(writeBytes == -1){
            perror("File write failed");
            close(fd);
            return 1;
        }
        totalBytesWrite+=writeBytes;
    }
    int sum=0;
    for(int i=0;i<5;i++){
        sum+=arr[i];
    }
    printf("Sum is [%d]\n",sum);
    printf("Writing sum to fifo\n");
    int sumWrite = write(fd,&sum,sizeof(sum));
    if(sumWrite == -1){
        perror("File write failed");
        close(fd);
        return 1;
    }
    printf("Wrote sum to FIFO\n");
    printf("Returning from fifoWriter\n");
    close(fd);
    return 0;
}