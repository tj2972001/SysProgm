#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void) {
    size_t BUF_SIZE = 200;
    char arr[BUF_SIZE];
    char *name = malloc(BUF_SIZE*sizeof(char));
    printf("Enter name\n");
    getdelim(&name,&BUF_SIZE,'@',stdin);
    printf("Name is %s!",name);
	return 0;
}
