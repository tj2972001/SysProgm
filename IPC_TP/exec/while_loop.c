/* Prints numbers from 1 to 10 using while loop */
/*
#include<stdio.h>

int main() {
   int value = 1;
   while (value <= 10) {
      printf("%d\t", value);
      value++;
   }
   printf("\n");
   return 0;
}
*/
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
   int start_value = 1;
   int end_value;
   if (argc == 1)
   end_value = 10;
   else
   end_value = atoi(argv[1]);
   printf("Argv[1] is %s\n", argv[1]);
   while (start_value <= end_value) {
      printf("%d\t", start_value);
      start_value++;
   }
   printf("\n");
   return 0;
}