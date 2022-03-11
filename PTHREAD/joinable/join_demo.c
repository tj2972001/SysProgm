#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void *r2(void *args)
{
    int *t2_ret_val = (int *)malloc(sizeof(int));
    *t2_ret_val = 2;
    sleep(3);
    return (void *)t2_ret_val;
}
void *r3(void *args)
{
    int *t3_ret_val = (int *)malloc(sizeof(int));
    *t3_ret_val = 3;
    sleep(1.5);
    return (void *)t3_ret_val;
}
int main()
{
    void *t2_ret = NULL;
    void *t3_ret = NULL;
    pthread_t t2, t3;
    pthread_attr_t t2attr, t3attr;
    pthread_attr_init(&t2attr);
    pthread_attr_init(&t3attr);
    pthread_attr_setdetachstate(&t2attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setdetachstate(&t3attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&t2, &t2attr, r2, t2_ret);
    pthread_create(&t3, &t3attr, r3, t3_ret);
    printf("Just before t2 join point\n");
    /*
    if (pthread_join(t2, &t2_ret) == -1)
    {
        perror("Failed to join t2\n");
        return 1;
    }
    printf("t2_ret is (%d)\n", *((int *)t2_ret));
    */
    printf("Just before t3 join point\n");
    /*
    pthread_join(t3, &t3_ret);
    printf("t3_ret is (%d)\n", *((int *)t3_ret));
    */
    return 0;
}