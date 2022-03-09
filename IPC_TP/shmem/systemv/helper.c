#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void* attach_sh_mem(int id, const void* addr, int flg){
    return shmat(id,addr,flg);
}

int detach_sh_mem(int* shm){
    return shmdt(shm);
}

int write_sh_mem(int id, int* shm, int n){
    printf("Writing to shared mem\n");
    srand(time(NULL));
    int ele = rand()%100;
    shm[0]  =ele;
    printf("Wrote [%d] to shared memory\n",ele);
    return 0;
}
int read_sh_mem(int id, int* shm){
    printf("reading from shared memory\n");
    int ele = shm[0];
    printf("Read [%d] from shared memory\n",ele);
    return 0;        
}

int create_sh_mem(size_t size, int key){
    return shmget(key,size,IPC_CREAT|0777);
}
