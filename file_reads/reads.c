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

// Rdtsc blocks
unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

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

int main()
{
	FILE *fp1; 
	fp1 = fopen("results.txt", "w+");

	char file_names[9][50];
	int file_sizes[9];

	const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	// Write a few hundred blocks of random data to the file *synchronously*
	int block_size_bytes = 4096;
	int number_of_blocks = 1000;

	int i = 0; 
	while(i < 9) {
		// Create a file
		char file_name[50];
		file_sizes[i] = number_of_blocks; 
		sprintf(file_name, "temp_file_%d", number_of_blocks);
		strcpy(file_names[i], file_name);

		if(fopen(file_name, "r") == 0) {
			int total_bytes = number_of_blocks * block_size_bytes;
			unsigned char* data = malloc(total_bytes);
			for(int i=0; i < total_bytes; i++)	data[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

			int fd = open(file_name, O_WRONLY|O_SYNC|O_CREAT);
			write(fd, data, total_bytes);
			close(fd);
		}
		i++;
		number_of_blocks *= 2; 
	}

	srand(time(0));
	uint64_t start, end, cpu_cycles_spent, sum_cpu_cycles_spent;

	for(int i = 0; i < 9; i++) {
		int fd2 = open(file_names[i], O_RDONLY|O_SYNC);
		if(fd2 == -1)	perror("File Open Error");

		int total_bytes = file_sizes[i] * block_size_bytes;
		// Read a random block directly from disk
		// O_DIRECT reads require buffer to be properly aligned.
		void* data_block;
		posix_memalign(&data_block, block_size_bytes, total_bytes);

		int total_random_cycles = 0; 
		for(int i=0; i<10000; i++)
		{
			//Random Access 
			int offset = (rand() % number_of_blocks) * block_size_bytes;

			rdtsc();
			int ret = lseek(fd2, offset, SEEK_SET);
			if(ret == -1)	perror("File Seek Error");
			ret = read(fd2, data_block, block_size_bytes);
			if(ret == -1)	perror("File Read Error");
			rdtsc1();

			start = ( ((uint64_t)cycles_high << 32) | cycles_low );
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
			cpu_cycles_spent = (end - start);

			total_random_cycles += cpu_cycles_spent; 
		}
	
		fd2 = open(file_names[i], O_RDONLY|O_SYNC);
		total_random_cycles/=10000; 
		int total_sequential = 0; 
		for(int i=0; i < 10000; i++)
		{
			//Sequential Access
			rdtsc();
			int ret = read(fd2, data_block, block_size_bytes);
			if(ret == -1)	perror("File Read Error");
			rdtsc1();

			start = ( ((uint64_t)cycles_high << 32) | cycles_low );
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
			cpu_cycles_spent = (end - start);

			total_sequential += cpu_cycles_spent;  
		}

		total_sequential/=10000; 
		fprintf(fp1, "%f %f %f\n", log(file_sizes[i]), log(total_random_cycles), log(total_sequential));
	}
}
