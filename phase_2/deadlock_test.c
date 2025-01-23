// // #include "types.h"
// // #include "user.h"
// // #include "stat.h"

// // Lock lock1, lock2;

// // void thread1_func(void *arg1, void *arg2)
// // {
// //     int *tid = (int *)arg2;

// //     // Request first resource
// //     if (requestresource(0) < 0)
// //     {
// //         printf(2, "Thread %d failed to request resource 0\n", *tid);
// //         exit();
// //     }

// //     // Simulate some work
// //     printf(2, "Thread %d got resource 0\n", *tid);

// //     // Request second resource
// //     if (requestresource(1) < 0)
// //     {
// //         printf(2, "Thread %d failed to request resource 1\n", *tid);
// //         releaseresource(0);
// //         exit();
// //     }

// //     printf(2, "Thread %d got resource 1 - Potential Deadlock!\n", *tid);

// //     // Release resources
// //     releaseresource(1);
// //     releaseresource(0);

// //     exit();
// // }

// // void thread2_func(void *arg1, void *arg2)
// // {
// //     int *tid = (int *)arg2;

// //     // Request resources in opposite order to create potential deadlock
// //     if (requestresource(1) < 0)
// //     {
// //         printf(2, "Thread %d failed to request resource 1\n", *tid);
// //         exit();
// //     }

// //     printf(2, "Thread %d got resource 1\n", *tid);

// //     // Request first resource
// //     if (requestresource(0) < 0)
// //     {
// //         printf(2, "Thread %d failed to request resource 0\n", *tid);
// //         releaseresource(1);
// //         exit();
// //     }

// //     printf(2, "Thread %d got resource 0 - Potential Deadlock!\n", *tid);

// //     // Release resources
// //     releaseresource(0);
// //     releaseresource(1);

// //     exit();
// // }

// // int main()
// // {
// //     int tid1 = 1, tid2 = 2;

// //     // Create two threads that might cause a deadlock
// //     thread_create(&thread1_func, 0, (void *)&tid1);
// //     thread_create(&thread2_func, 0, (void *)&tid2);

// //     // Wait for threads to complete
// //     join(tid1);
// //     join(tid2);

// //     printf(0, "Deadlock detection test completed\n");
// //     exit();
// // }

// // // #include "types.h"
// // // #include "user.h"

// // // int main()
// // // {
// // //     if (requestresource(0) == 0)
// // //     {
// // //         printf(1, "Resource 0 acquired\n");
// // //         releaseresource(0);
// // //         printf(1, "Resource 0 released\n");
// // //     }
// // //     else
// // //     {
// // //         printf(1, "Failed to acquire Resource 0\n");
// // //     }
// // //     exit();
// // // }

// #include "types.h"
// #include "user.h"
// #include "stat.h"

// void thread1_func(void *arg1, void *arg2)
// {
//     int *tid = (int *)arg2;
//     int retry_count = 3; // Add retry mechanism

//     while (retry_count > 0)
//     {
//         // Request first resource
//         if (requestresource(0) == 0)
//         {
//             printf(2, "Thread %d got resource 0\n", *tid);

//             // Try to get second resource
//             if (requestresource(1) == 0)
//             {
//                 printf(2, "Thread %d got resource 1\n", *tid);

//                 // Simulate some work
//                 sleep(10);

//                 // Release resources in reverse order
//                 releaseresource(1);
//                 releaseresource(0);
//                 exit();
//             }
//             else
//             {
//                 // If second resource fails, release first
//                 releaseresource(0);
//             }
//         }

//         retry_count--;
//         sleep(10); // Wait before retrying
//     }

//     printf(2, "Thread %d failed to acquire resources\n", *tid);
//     exit();
// }

// void thread2_func(void *arg1, void *arg2)
// {
//     int *tid = (int *)arg2;
//     int retry_count = 3; // Add retry mechanism

//     while (retry_count > 0)
//     {
//         // Request first resource
//         if (requestresource(1) == 0)
//         {
//             printf(2, "Thread %d got resource 1\n", *tid);

//             // Try to get second resource
//             if (requestresource(0) == 0)
//             {
//                 printf(2, "Thread %d got resource 0\n", *tid);

//                 // Simulate some work
//                 sleep(10);

//                 // Release resources in reverse order
//                 releaseresource(0);
//                 releaseresource(1);
//                 exit();
//             }
//             else
//             {
//                 // If second resource fails, release first
//                 releaseresource(1);
//             }
//         }

//         retry_count--;
//         sleep(10); // Wait before retrying
//     }

//     printf(2, "Thread %d failed to acquire resources\n", *tid);
//     exit();
// }

// int main()
// {
//     int tid1 = 1, tid2 = 2;

//     // Create two threads that might cause a deadlock
//     if (thread_create(&thread1_func, 0, (void *)&tid1) < 0)
//     {
//         printf(2, "Failed to create thread 1\n");
//         exit();
//     }

//     if (thread_create(&thread2_func, 0, (void *)&tid2) < 0)
//     {
//         printf(2, "Failed to create thread 2\n");
//         exit();
//     }

//     // Wait for threads to complete
//     join(tid1);
//     join(tid2);

//     printf(0, "Deadlock detection test completed\n");
//     exit();
// }

#include "types.h"
#include "user.h"
#include "stat.h"

void thread1_func(void *arg1, void *arg2)
{
    int *tid = (int *)arg2;
    int r1 = requestresource(0);
    int r2 = requestresource(1);

    if (r1 == 0 && r2 == 0)
    {
        printf(2, "Thread %d acquired both resources\n", *tid);
        sleep(10);
        releaseresource(1);
        releaseresource(0);
    }
    else
    {
        if (r1 == 0)
            releaseresource(0);
        if (r2 == 0)
            releaseresource(1);
        printf(2, "Thread %d resource acquire failed: r1=%d, r2=%d\n", *tid, r1, r2);
    }
    exit();
}

void thread2_func(void *arg1, void *arg2)
{
    int *tid = (int *)arg2;
    int r1 = requestresource(1);
    int r2 = requestresource(0);

    if (r1 == 0 && r2 == 0)
    {
        printf(2, "Thread %d acquired both resources\n", *tid);
        sleep(10);
        releaseresource(0);
        releaseresource(1);
    }
    else
    {
        if (r1 == 0)
            releaseresource(1);
        if (r2 == 0)
            releaseresource(0);
        printf(2, "Thread %d resource acquire failed: r1=%d, r2=%d\n", *tid, r1, r2);
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