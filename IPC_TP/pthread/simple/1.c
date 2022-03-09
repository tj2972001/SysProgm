#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
int main(){
    printf("Hello from main\n");
    printf("Current thread id is [%d]\n",gettid());
    return 0;
}