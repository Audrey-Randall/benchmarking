
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
unsigned cycles_low, cycles_high;

static __inline__ unsigned long long rdtsc(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "rbx", "rcx", "rdx");
}

int main()
{
    int i, cpu_id, cpid, max_trials = 100;
	int p2c_pipe[2];
	int c2p_pipe[2];
	uint64_t time_child, time_parent, time_spent, avg_time_spent = 0, dummy_time = 0;

    // printf("Parent PID: %d\n", getpid());

    // Get the CPU on which the thread is running
    cpu_id = sched_getcpu();

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

	// Create pipes
	pipe(p2c_pipe);
	pipe(c2p_pipe);


	cpid = fork();
	if (cpid == 0) 
	{
		// Child process
		close(c2p_pipe[0]);
		close(p2c_pipe[1]);

		// First synchronization
		write(c2p_pipe[1], &dummy_time, sizeof(dummy_time));	

		for(i=0;i<max_trials;i++)
		{
			// Wait for parent to write
			read(p2c_pipe[0], &dummy_time, sizeof(dummy_time));
			
			// Collect time and write to parent
			rdtsc();
			time_child = ( ((uint64_t)cycles_high << 32) | cycles_low );
			// printf("C - %lu\n", time_child);
			write(c2p_pipe[1], &time_child, sizeof(time_child));
		}
	}
	else
	{
		// Parent process
		close(c2p_pipe[1]);
		close(p2c_pipe[0]);

		// First synchronization
		read(c2p_pipe[0], &dummy_time, sizeof(dummy_time));

		for(i=0;i<max_trials;i++)
		{
			// Write to unblock child
			write(p2c_pipe[1], &dummy_time, sizeof(dummy_time));
			
			// Read from child, get current time and calculate time diff
			read(c2p_pipe[0], &time_child, sizeof(time_child));
			rdtsc();
			time_parent = ( ((uint64_t)cycles_high << 32) | cycles_low );
			// printf("P - %lu\n", time_parent);

			time_spent = time_parent - time_child;
			// printf("D - %lu\n", time_spent);
			avg_time_spent += time_spent;
		}

		printf("Parent CPU ID: %d, Avg. context switch time: %lf\n", cpu_id, avg_time_spent*1.0/max_trials);
	}

    return 0;
}
