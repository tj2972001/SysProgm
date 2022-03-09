#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sig_stp_handler(int sig){
    printf("Continuining\n");
}
int main(){
    int num;
    struct sigaction sa;
    //sa.sa_flags = SA_RESTART;
    // sa.sa_handler = &sig_stp_handler;
    // printf("mask is %d\n",sa.sa_mask);
    // sigaction(SIGTSTP,&sa,NULL);
    void (*sigHandler)(int);
    sigHandler = signal(SIGTSTP,&sig_stp_handler);
    //sigHandler(10);
    // sleep(5);
    // raise(SIGFPE);
    printf("mask is %d\n",sa.sa_mask);
    printf("Enter a number\n");
    scanf("%d",&num);
    printf("You enetered %d\n",num);
    return 0;
}