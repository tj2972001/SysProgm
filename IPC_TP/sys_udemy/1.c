#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<errno.h>
#include<pwd.h>
#define FILE_PERM 0111
int machine_endianness(unsigned short int a){
    printf("sizeof unsigned short is %lu\n",sizeof(unsigned short int));
    printf("size of char* is %lu\n",sizeof(char*));
    char t = *((char*)&a);
    printf("t is %d\n",t);
    return t;
}
int main(){
    int data=20;
    char* pathname = "/Users/tejadhav/Desktop/demo.txt";
    int fd = open(pathname,O_CREAT|O_EXCL);
    struct passwd * pwd = getpwuid(getuid());
    printf("pwname: %s\n",pwd==NULL?"NO":pwd->pw_name);
    if(fd==-1){
        perror("Error occured");
        printf("Errno: [%d]\n",errno);
    }
    machine_endianness(10);
    machine_endianness(11);
    machine_endianness(14);
    machine_endianness(1);
    printf("00012312 is %o\n",00012312);
    return 0;
}