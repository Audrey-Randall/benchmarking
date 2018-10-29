#include <stdio.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 

#define num_threads 1000
#define num_processes 100000

pthread_t tid[num_threads];
pid_t processes[num_processes];

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

int runProcess(int i, char * argv[]) {
	processes[i] = fork();
	return processes[i];
}

void *func() {
	return NULL; 
}

//Creating pthread 
int runKernelThread(int i) {
	int err = pthread_create(&(tid[i]), NULL, &func, NULL);
	return 0; 
}

int main() {
	uint64_t start, end; 
	char * argv[3];
	argv[0] = "first";
	argv[1] = "second";
	argv[2] = NULL;

	struct timeval t1, t2;
	int process_thread_time, kernel_thread_time, id;

	//Create Kernel level threads 
    rdtsc();
	int i = 0;
	while(i < num_threads) {
		runKernelThread(i);
		i++;
	}
    rdtsc1();
	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	kernel_thread_time = (end - start)/(num_threads * 1.0);
	fprintf(stdout, "Kernel Thread time: %d\n", kernel_thread_time);

	//Create process
    rdtsc();
    i = 0; 
	while(i < num_processes) {
		id = runProcess(i, argv);
		if(id == -1) break;
		i++;
	}
    rdtsc1();

    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
	process_thread_time = (end - start)/(num_processes * 1.0);	
	fprintf(stdout, "Process Thread time: %d\n", process_thread_time);
}




