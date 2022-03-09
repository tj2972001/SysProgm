#include<sys/types.h>
int create_sh_mem(size_t size, int key);
int read_sh_mem(int id, int* shm);
int write_sh_mem(int id, int* shm, int n);
void* attach_sh_mem(int id, const void* addr, int flg);
int detach_sh_mem(int* shm);