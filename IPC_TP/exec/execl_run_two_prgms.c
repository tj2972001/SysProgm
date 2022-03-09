/*
#include<stdio.h>
#include<unistd.h>

int main() {
   int pid;
   pid = fork();
   printf("PID is [%d]\n",getpid());
   //Child process
   if (pid == 0) {
      printf("Child process: Running Hello World Program\n");
      execl("./helloworld", "./helloworld", (char *)0);
      printf("This wouldn't print\n");
   } else { // Parent process 
      sleep(3);
      printf("Parent process: Running While loop Program\n");
      execl("./while_loop", "./while_loop", (char *)0);
      printf("Won't reach here\n");
   }
   printf("Won't reach here as well\n");
   return 0;
}*/

/*
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[0]) {
   int pid;
   int err;
   int num_times;
   char num_times_str[5];
   
   
   if (argc == 1) {
      printf("Taken loop maximum as 10\n");
      num_times = 10;
      sprintf(num_times_str, "%d", num_times);
   } else {
      strcpy(num_times_str, argv[1]);
      printf("num_times_str is %s\n", num_times_str);
      pid = fork();
   }
   
   if (pid == 0) {
      printf("Child process: Running Hello World Program\n");
      err = execl("./helloworld", "./helloworld", (char *)0);
      printf("Error %d\n", err);
      perror("Execl error: ");
      printf("This wouldn't print\n");
   } else {
      sleep(3);
      printf("Parent process: Running While loop Program\n");
      execl("./while_loop", "./while_loop", (char *)num_times_str, (char *)0);
      printf("Won't reach here\n");
   }
   printf("Won't reach here as well\n");
   return 0;
}
*/
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    const int MAX_BUFFER_SIZE=50;
    char buffer[MAX_BUFFER_SIZE];
    int fd = open("/Users/tejadhav/Desktop/a.txt",O_RDONLY);
    int r = read(fd,buffer,sizeof(buffer));
    write(1,buffer,r);
    return 0;
}