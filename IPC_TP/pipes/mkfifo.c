#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(){
    const int FIFO_PER = 0777;
    const char* pathname = "sum";
    if(mkfifo(pathname,FIFO_PER)==-1){
        perror("FIFO creation failed");
        return 1;
    }
    printf("Fifo created successfully\n");
    return 0;
}