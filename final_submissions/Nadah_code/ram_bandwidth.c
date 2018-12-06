#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <math.h>
#include <string.h>
//#include "util.h"

unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

#define max_trials 20
#define ARRAY_SIZE 150000

static __inline__ unsigned long long rdtsc(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "rbx", "rcx", "rdx");
    return 0;
}

static __inline__ unsigned long long rdtsc1(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
            "%rax", "rbx", "rcx", "rdx");
    return 0;
}

int memReads() {
	int readArr[ARRAY_SIZE];
	float time[ARRAY_SIZE];
	int start, end;

	float sum = 0;
	int i = 0;
	int j = 0;
	int x = 0;

	for(i = 0; i < ARRAY_SIZE/16; i++) {
		for(j = i; j < ARRAY_SIZE; j+=16) {
			sum += readArr[j];

        	sum += (end - start);
		}
	}
	return sum / ARRAY_SIZE;

}

void memWrites() {
	int writeArr[ARRAY_SIZE];
	int i = 0;
	int j = 0;

	for(i = 0; i < ARRAY_SIZE/16; i++) {
		for(j = i; j < ARRAY_SIZE; j+=16) {
			writeArr[j] = j;
		}
	}
}

int main()
{
	float time_spent, avg_time_spent = 0;
	int i;
	int start, end;

    for(i=0;i<max_trials;i++)
    {
    	rdtsc();
		memReads();
		rdtsc1();
		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = (end - start)/ARRAY_SIZE;
        avg_time_spent += time_spent;
    }
    printf("Bandwidth for reading from memory: %lf cycles\n", avg_time_spent*1.0/max_trials);

	for(i=0;i<max_trials;i++)
    {
		rdtsc();
		memWrites();
		rdtsc1();

		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
		end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
        time_spent = (end - start)/ARRAY_SIZE;
        avg_time_spent += time_spent;
    }
    printf("Bandwidth for writing to memory: %lf cycles\n", avg_time_spent*1.0/max_trials);
	return 0;
}
