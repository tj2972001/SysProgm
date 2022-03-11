#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
void *r1(void *args)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);
    char str[100];
    for (int t = 0; t < 100; t++)
    {
        printf("%d\n", t);
        snprintf(str, sizeof(str), "This should print until 100 in Deferred - %d\n", t);
    }
    pthread_testcancel();
}

int main()
{

    pthread_t t1;
    void *t1_ret = NULL;
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);
    pthread_create(&t1, 0, r1, 0);
    printf("Cancelling thread\n");
    if (pthread_cancel(t1) == -1)
    {
        perror("Failed to cancel thread\n");
        return 1;
    }
    printf("Thread cancelled and cleaned up successfully\n");
    printf("Returning from main\n");
    pthread_exit(0);
}