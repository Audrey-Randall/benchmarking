
#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


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
    int i, cpu_id, cpid, max_trials = 100;
	int pipefd[2];

    printf("Parent PID: %d\n", getpid());

    // Get the CPU on which the thread is running
    cpu_id = sched_getcpu();
    printf("Parent CPU ID: %d\n", cpu_id);

	// Set parent CPU affinity. It'll be inherited by the child as well.
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


	uint64_t start, end, time_spent, avg_time_spent = 0;
	for(i=0;i<max_trials;i++)
	{
		// Create pipe
		pipe(pipefd);

		// Start timer
		rdtsc();
		cpid = fork();
		if (cpid == 0) 
		{
			// Child process: collect time diff
			rdtsc1();
			start = ( ((uint64_t)cycles_high << 32) | cycles_low );
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
			time_spent = end - start;		
			//cpu_id = sched_getcpu();
			//printf("Child CPU ID: %d\n", cpu_id);
			// printf("%lu\n", time_spent);
			
			// Write the time diff to parent
			close(pipefd[0]);
			write(pipefd[1], &time_spent, sizeof(time_spent));
			close(pipefd[1]);
			
			exit(0);
		}
		else
		{
			// Parent: Read the time diff from child (also forces a context switch)
			close(pipefd[1]);
			read(pipefd[0], &time_spent, sizeof(time_spent));
			close(pipefd[0]);
		
			// printf("%lu\n", time_spent);
			avg_time_spent += time_spent;

			// Wait for child
			wait(NULL);
		}
	}

	printf("\nAvg. context switch time: %lf\n", avg_time_spent*1.0/max_trials);

    return 0;
}
