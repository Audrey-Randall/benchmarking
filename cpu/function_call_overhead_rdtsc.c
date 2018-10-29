
#define _GNU_SOURCE
#define N (1024*4)
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <math.h>


double stdev(double* vals, int len){
	  double avg = 0.0;
	  for(int i = 0; i < len; i++) {
			avg += vals[i];
	  }
	  avg /= len;
	  double std = 0;
	  for(int i = 0; i < len; i++) {
			double diff = vals[i] - avg;
			std += (diff*diff);
	  }
	  double new_std = sqrt(std/len);
	  return new_std;
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
    // printf("CPU ID: %d\n", cpu_id);

	// Set parent CPU affinity. It'll be inherited by the child as well - this will restrict both processes to one core.
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(cpu_id, &set);
	sched_setaffinity(getpid(), sizeof(set), &set);

	// Set process priority (nice value) to the highest. This will be inherited by the child process as well.
	if(setpriority(PRIO_PROCESS, getpid(), -20) != 0)
	{
		perror("Setting process priority failed!");
		exit(-1);
	}

	FILE* fp = fopen ("0_args.txt", "a+");
    uint64_t time_spent;
	double avg_time_spent = 0, total_time_spent = 0, records[max_trials];
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
		test_procedure_0();
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


	fp = fopen ("1_args.txt", "a+");
    total_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_1(1);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


	fp = fopen ("2_args.txt", "a+");
    total_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_2(1,2);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


	fp = fopen ("3_args.txt", "a+");
    total_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_3(1,2,3);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


	fp = fopen ("4_args.txt", "a+");
    total_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_4(1,2,5,6);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


	fp = fopen ("5_args.txt", "a+");
    total_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_5(1,2,5,6,10);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


	fp = fopen ("6_args.txt", "a+");
    total_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_6(1,2,5,6,4,100);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


	fp = fopen ("7_args.txt", "a+");
    total_time_spent = 0;
    for(i=0;i<max_trials;i++)
    {
		rdtsc();
        test_procedure_7(1,2,5,6,4,100,200);
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = end - start;
		// printf("%lu, ", time_spent);
        total_time_spent += time_spent;
		records[i] = time_spent;
    }
    // printf("%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));
    fprintf(fp, "%lf, %lf\n", total_time_spent*1.0/max_trials, stdev(records, max_trials));


    // Get the CPU on which the thread is running
    cpu_id = sched_getcpu();
    // printf("======================================\n");

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
