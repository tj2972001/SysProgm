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
    int key = ftok("/Users/tejadhav/Desktop/a.txt",0); /* This will create unique key */
    printf("Key is [%d]\n",key);
    int id = create_sh_mem(BUF_SIZE,key);
    printf("Attaching shared memory\n");
    int* shm = (int*)attach_sh_mem(id,NULL,0);
    printf("Shared memory attched\t status: [%d]\n",*shm);
    int readStatus = read_sh_mem(id,shm);
    printf("Read ended\tstatus: [%d]\n",readStatus);
    printf("Detaching shared memory from process main_consumer\n");
    int detachStatus = detach_sh_mem(shm);
    printf("Detached shared memory\tstatus: [%d]\n",detachStatus);
    return 0;
}