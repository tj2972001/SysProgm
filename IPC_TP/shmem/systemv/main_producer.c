#include<sys/ipc.h>
#include<errno.h>
#include<stdbool.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

#include"helper.h"

int main(){
    const size_t BUF_SIZE = 1024;
    printf("Creating shared memory of 1024 Bytes\n");
    int key = ftok("/Users/tejadhav/Desktop/a.txt",0);
    printf("Key is [%d]\n",key);
    int id = create_sh_mem(BUF_SIZE,key);
    printf("Attaching shared memory\n");
    int* shm = (int*)attach_sh_mem(id,NULL,0);
    printf("Attched shared memory\t status: [%d]\n",*shm);
    int n =10;
    int writeStatus = write_sh_mem(id,shm,n);
    printf("Write ended\tstatus: [%d]\n",writeStatus);   
    int detachStatus = detach_sh_mem(shm);
    printf("Detached shared memory\tstatus: [%d]\n",detachStatus); 
    return 0;
}