#include "types.h"
#include "user.h"
#include "stat.h"

void thread1_func(void *arg1, void *arg2)
{
    int *tid = (int *)arg2;
    int r0 = requestresource(0);
    sleep(300);
    int r1 = requestresource(1);

    if (r1 == 0 && r0 == 0)
    {
        printf(2, "Thread %d acquired both resources\n", *tid);
        sleep(200);
        releaseresource(1);
        sleep(100);
        releaseresource(0);
        printf(2, "Thread %d released both resources\n", *tid);
    }
    else
    {
        printf(2, "Thread %d resource acquire failed: r1=%d, r0=%d\n", *tid, r1, r0);
        sleep(200);
        if (r1 == 0){
            releaseresource(1);
            printf(2, "Thread %d released r1 resources\n", *tid);
        }
        if (r0 == 0){
            releaseresource(0);
            printf(2, "Thread %d released r0 resources\n", *tid);
        }
    }
    exit();
}

void thread2_func(void *arg1, void *arg2)
{
    int *tid = (int *)arg2;
    int r1 = requestresource(1);
    sleep(300);
    int r0 = requestresource(0);

    if (r1 == 0 && r0 == 0)
    {   
        printf(2, "Thread %d acquired both resources\n", *tid);
        sleep(200);
        releaseresource(0);
        sleep(100);
        releaseresource(1);
    }
    else
    {
        printf(2, "Thread %d resource acquire failed: r1=%d, r0=%d\n", *tid, r1, r0);
        sleep(200);
        if (r1 == 0){
            releaseresource(1);
            printf(2, "Thread %d released r1 resources\n", *tid);
        }
        if (r0 == 0){
            releaseresource(0);
            printf(2, "Thread %d released r0 resources\n", *tid);
        }
    }
    exit();
}

int main()
{
    int tid1 = 1, tid2 = 2;

    // Verbose thread creation logging
    int th1 = thread_create(&thread1_func, 0, (void *)&tid1);
    int th2 = thread_create(&thread2_func, 0, (void *)&tid2);

    printf(2, "Thread 1 creation: %d, Thread 2 creation: %d\n", th1, th2);

    if (th1 < 0 || th2 < 0)
    {
        printf(2, "Thread creation failed\n");
        exit();
    }

    join(tid1);
    join(tid2);

    printf(0, "Deadlock test completed\n");
    exit();
}