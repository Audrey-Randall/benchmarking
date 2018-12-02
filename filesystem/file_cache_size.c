#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h> 
#include <math.h>
#include <errno.h>
#include <string.h>


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


int main()
{
	srand(time(0));

	// Set process priority (nice value) to the highest to avoid unnecessary waits.
	if(setpriority(PRIO_PROCESS, getpid(), -20) != 0)
	{
		perror("Setting process priority failed!");
		exit(-1);
	}


	// Parameters
	uint64_t step_size_mb = 1000;
	uint64_t max_size_mb = 10*pow(2, 10);	// 10GB
	uint64_t step_sized_int_array_size = (step_size_mb*1024*1024)/sizeof(int);
	int* step_sized_int_array = (int*)malloc(step_sized_int_array_size*sizeof(int));
	int max_trials = 1000000;


	// Create the file
	char* file_name = "temp_file.txt";
	remove(file_name);
	FILE* fp = fopen(file_name, "a+");
	uint64_t start, end, cpu_cycles_spent, sum_cpu_cycles_spent;

	for(uint64_t file_size_mb = 1000; file_size_mb <= max_size_mb; file_size_mb += step_size_mb)
	{
		// Increase file size by step size by writing an array of random integers 
		for(uint64_t i=0; i < step_sized_int_array_size; i++)	step_sized_int_array[i] = rand();
		fwrite(step_sized_int_array, sizeof(int), step_sized_int_array_size, fp);
		// printf("File size: %ld MB\n", ftell(fp)/(1024*1024));

		uint64_t file_size_ints = (file_size_mb*1024*1024)/sizeof(int);
		// printf("%lu %lu %lu\n", file_size_ints, file_size_ints*4/(1024*1024), rand_posn_in_file);

		sum_cpu_cycles_spent = 0;
		for(int trials = 0; trials < max_trials; trials++)
		{
			uint64_t rand_posn_in_file = (rand() % file_size_ints)*sizeof(int);
			int temp;

			rdtsc();
			fseek(fp, rand_posn_in_file, SEEK_SET);
			fread(&temp, sizeof(int), 1, fp);
			rdtsc1();

			start = ( ((uint64_t)cycles_high << 32) | cycles_low );
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
			cpu_cycles_spent = (end - start);
			sum_cpu_cycles_spent += cpu_cycles_spent;
		}
		
		printf("%lu %lf\n", file_size_mb, sum_cpu_cycles_spent*1.0/max_trials);
	}

	fclose(fp);
	remove(file_name);
}
