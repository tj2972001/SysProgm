#include<stdio.h>
#include<unistd.h>
int main() {
   printf("Hello from %d\n",getpid());
   int x; 
   printf("Enter a number\n"); 
   scanf("%d",&x);
   printf("You enetered %d\n",x);
   //fflush(stdin);
   //fflush(stdout);
   int id = fork();
   if(id==-1){
      printf("Fork failed\n");
   }else if(id==0){
      printf("Child process %d\n",getpid());
   }else{
      printf("Parent process %d\n",getpid());
   }
   printf("Hello World\n");
   return 0;
}
