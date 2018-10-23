
#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>



// Assumes long int on 64-bit can hold seconds and nanoseconds together
long time_diff_in_ns(struct timespec start, struct timespec finish)
{
    long seconds = finish.tv_sec - start.tv_sec;
    long ns = finish.tv_nsec - start.tv_nsec;
    if (start.tv_nsec > finish.tv_nsec) {
        --seconds;
        ns += 1000000000;
    }
    return seconds*1000000000 + ns;
}

void test_procedure_0()
{
}

void test_procedure_1(int arg1)
{
}

void test_procedure_2(int arg1, int arg2)
{
}

void test_procedure_3(int arg1, int arg2, int arg3)
{
}

void test_procedure_4(int arg1, int arg2, int arg3, int arg4)
{
}

void test_procedure_5(int arg1, int arg2, int arg3, int arg4, int arg5)
{
}

void test_procedure_6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
}

void test_procedure_7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7)
{
}

int main()
{
    struct timespec start, finish;
    long time_spent;
    int i, cpu_id, max_trials = 100;

    // Get the CPU on which the thread is running
    cpu_id = sched_getcpu();
    printf("CPU ID: %d\n", cpu_id);

    long avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_0();
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        int a = 1;
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_1(1);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_2(1,2);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_3(1,2,3);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_4(1,2,5,6);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_5(1,2,5,6,10);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_6(1,2,5,6,4,100);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
        clock_gettime(CLOCK_REALTIME, &start);
        test_procedure_7(1,2,5,6,4,100,200);
        clock_gettime(CLOCK_REALTIME, &finish);
        time_spent = time_diff_in_ns(start, finish);
        avg_time_spent += time_spent;
        // printf("%ld, ", time_spent);
    }
    printf("%lfns\n", avg_time_spent*1.0/max_trials);

    // Get the CPU on which the thread is running
    cpu_id = sched_getcpu();
    printf("CPU ID: %d\n", cpu_id);

    return 0;
}


void time_diff_in_ns_v1(struct timespec start, struct timespec finish, struct timespec *diff)
{
    long seconds = finish.tv_sec - start.tv_sec;
    long ns = finish.tv_nsec - start.tv_nsec;
    if (start.tv_nsec > finish.tv_nsec) {
        --seconds;
        ns += 1000000000;
    }

    diff->tv_sec = seconds;
    diff->tv_nsec = ns;
}
