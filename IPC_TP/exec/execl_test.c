#include<stdio.h>
#include<unistd.h>
int main() {
   execl("./helloworld.o", "./helloworld.o", (char *)0);
   printf("This wouldn't print\n");
   return 0;
}
