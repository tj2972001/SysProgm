#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

int main(){
    printf("In fifoReader main\n");
    int q;
    const char* filename = "sum";  // Name of FIFO
    int fd = open(filename,O_RDONLY); // Open FIFO
    if(fd==-1){
        perror("File open failed");
        return 1;
    }
    int totalBytesRead = 0;
    for(int i=0;i<5;i++){
        int readStatus = read(fd,&q,sizeof(int));
        if(readStatus==-1){
            perror("File read failed");
            close(fd);
            return 1;
        }
        totalBytesRead+=readStatus;
        printf("Read [%d] from file\n",q);
    }
    printf("Read [%d] Bytes from FIFO [%s]\n",totalBytesRead,filename);
    printf("Reading sum from fifo\n");
    int sum;
    int readSum = read(fd,&sum,sizeof(sum));
    if(readSum == -1){
        perror("File read failed");
        close(fd);
        return 1;
    }
    printf("Read sum successfully. Sum is [%d]\n",sum);
    printf("Returning from fifoReader\n");
    close(fd);
    return 0;
}