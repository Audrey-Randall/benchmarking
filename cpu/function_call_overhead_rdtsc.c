
#define _GNU_SOURCE
#define N (1024*4)
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
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


// Rdtsc blocks
unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

static __inline__ unsigned long long rdtsc(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "rbx", "rcx", "rdx");
}

static __inline__ unsigned long long rdtsc1(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
            "%rax", "rbx", "rcx", "rdx");
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
    uint64_t start, end;
    int i, cpu_id, max_trials = 100;

    // Get the CPU on which the thread is running
    cpu_id = sched_getcpu();
    printf("CPU ID: %d\n", cpu_id);

    uint64_t time_spent, avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
		test_procedure_0();
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("0 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);


    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_1(1);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("1 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);


    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_2(1,2);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("2 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);


    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_3(1,2,3);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("3 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);

    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_4(1,2,5,6);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("4 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);


    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_5(1,2,5,6,10);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("5 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);


    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_6(1,2,5,6,4,100);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("6 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);


    avg_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_7(1,2,5,6,4,100,200);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
        avg_time_spent += time_spent;
    }
    printf("7 arguments: %lf cycles\n", avg_time_spent*1.0/max_trials);


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
