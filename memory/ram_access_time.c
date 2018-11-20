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
	unsigned long max_size = pow(2, 30) + 1, max_iterations_per_stride = 1000000, max_stride = 100000;
	int* arr;	
    uint64_t start, end, cycles_spent, total_cycles_spent;
	double avg_cycles_spent;
	srand(time(NULL));
	
	for(int size=2; size < max_size; size *= 2)
	{
		int stride_max = size < max_stride ? size : max_stride;
		for(int stride = 2; stride < stride_max;stride *= 2)
		{
			arr = (int*)malloc(size*sizeof(int));

			unsigned long next_access = 0, counter = 0;
			int temp;
			total_cycles_spent = 0;
			
			/*for(int j=0; j<iterations;j++)
			{
				rdtsc();
				temp = arr[next_access];
				rdtsc1();
				
				start = ( ((uint64_t)cycles_high << 32) | cycles_low );
				end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
				total_cycles_spent += (end - start);

				next_access = (next_access + stride)%size;
			}*/

			
			while(next_access < size && counter < max_iterations_per_stride)
			{
				rdtsc();
				temp = arr[next_access];
				rdtsc1();

				start = ( ((uint64_t)cycles_high << 32) | cycles_low );
				end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
				total_cycles_spent += (end - start);
				// printf("%d %d %d %lu\n", size, stride, counter, (end - start));
				
				counter++;
				next_access += stride;	
			}

			avg_cycles_spent = total_cycles_spent*1.0/counter;
			printf("%d %d %lf\n", size, stride, avg_cycles_spent);
			
			free(arr);
		}		
	}
}
