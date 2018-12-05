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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <malloc.h>
#include <assert.h>


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
	const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	uint64_t start, end, cpu_cycles_spent, sum_cpu_cycles_spent;
	int max_processes = 50, max_read_count=1000;
	int child_processes[max_processes];

	// Set process priority (nice value) to the highest to avoid unnecessary waits.
	if(setpriority(PRIO_PROCESS, getpid(), -20) != 0)
	{
		perror("Setting process priority failed!");
		exit(-1);
	}

	// Spawn processes
	int cpid;
	for(int processes_count=0; processes_count < max_processes; processes_count += 1)
	{
		for(int i=0; i < processes_count; i++)
		{
			cpid = fork();
			if(cpid == 0)
			{
				// As a child, create a temp file with some data and read random blocks continuously until terminated by parent.

				// Create a temp file
				char file_name[50];
				sprintf(file_name, "temp_file_%d", getpid());

				// Write a few hundred blocks of random data to the file *synchronously*
				int block_size_bytes = 4096, number_of_blocks = 1000;
				int total_bytes = number_of_blocks*block_size_bytes;
				unsigned char* data = malloc(total_bytes);
				for(int i=0; i < total_bytes; i++)	data[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

				int fd = open(file_name, O_WRONLY|O_SYNC|O_CREAT);
				write(fd, data, strlen(data));
				close(fd);
				
				// Read a random block directly from disk, and keep doing it forever.
				// O_DIRECT reads require buffer to be properly aligned.
				int fd2 = open(file_name, O_RDONLY|O_DIRECT|O_SYNC);
				if(fd2 == -1)	perror("File Open Error");
				char* data_block = memalign(block_size_bytes, total_bytes);
				while(1)
				{
					// printf("Process %d: still reading\n", getpid());
					int offset = (rand() % number_of_blocks) * block_size_bytes;
					int ret = lseek(fd2, offset, SEEK_SET);
					if(ret == -1)	perror("File Seek Error");
					ret = read(fd2, data_block, block_size_bytes);
					if(ret == -1)	perror("File Read Error");
				}

				exit(-1);
			}
			else
			{
				child_processes[i] = cpid;
			}
		}
		
		// Parent reaches here after spawning all the child processes that start to poll the disk continuously.
		// Parent does the same, only difference is parent is taking the measurements too.
			
		// Create a temp file
		char file_name[50];
		sprintf(file_name, "temp_file_%d", getpid());
		// printf("%s\n", file_name);

		// Write a few hundred blocks of random data to the file *synchronously*
		int block_size_bytes = 4096, number_of_blocks = 1000;
		int total_bytes = number_of_blocks*block_size_bytes;
		unsigned char* data = malloc(total_bytes);
		for(int i=0; i < total_bytes; i++)	data[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

		int fd = open(file_name, O_WRONLY|O_SYNC|O_CREAT);
		write(fd, data, strlen(data));
		close(fd);
		
		// Read a random block directly from disk
		// O_DIRECT reads require buffer to be properly aligned.
		int fd2 = open(file_name, O_RDONLY|O_DIRECT|O_SYNC);
		if(fd2 == -1)	perror("File Open Error");
		char* data_block = memalign(block_size_bytes, total_bytes);
		sum_cpu_cycles_spent = 0;
		for(int i = 0; i < max_read_count; i++)
		{
			int offset = (rand() % number_of_blocks) * block_size_bytes;
			// printf("offset: %d\n", offset);	

			rdtsc();
			int ret = lseek(fd2, offset, SEEK_SET);
			if(ret == -1)	perror("File Seek Error");
			ret = read(fd2, data_block, block_size_bytes);
			if(ret == -1)	perror("File Read Error");
			rdtsc1();

			start = ( ((uint64_t)cycles_high << 32) | cycles_low );
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
			cpu_cycles_spent = (end - start);
			sum_cpu_cycles_spent += cpu_cycles_spent;

			// printf("%d %lu\n", processes_count+1, cpu_cycles_spent);
		}

		printf("%d %lf\n", processes_count+1, sum_cpu_cycles_spent*1.0/max_read_count);
			
		// Kill all the child processes and wait for them to stop.
		for(int i = 0; i < processes_count; i++)
		{
			kill(child_processes[i], SIGKILL);
			wait(NULL);
		}
	}
}
