#include<stdio.h>
int main(){
    const int MAX_BUF_SIZE = 100;
    char buffer[MAX_BUF_SIZE];
    printf("Enter i/p\n");

    while(fgets(buffer,MAX_BUF_SIZE,stdin)!=NULL){
        puts(buffer);
        printf("while");
    };
    printf("exit while\n");
    return 0;
}