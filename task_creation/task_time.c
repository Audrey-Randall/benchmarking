#include <stdio.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <math.h>

#define num_threads 100
#define num_processes 100
#define runs 100

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

double stdev(double* vals, int len){
  double avg = 0.0;
  for(int i = 0; i < len; i++) {
    avg+= vals[i];
  }
  avg /= len;
  double std = 0;
  for(int i = 0; i < len; i++) {
    double diff = vals[i] - avg;
    std += (diff*diff);
    //printf("%lf ", diff*diff);
  }
  double new_std = sqrt(std/len);
  printf("FUNCTION Avg: %lf Stdev: %lf\n", avg, new_std);
  return new_std;
}

int runProcess(int i, char * argv[]) {
	processes[i] = fork();
	if(processes[i] == 0) {
		execv(*argv, argv);
		exit(0);
	} else if(processes[i] > 0) waitpid(processes[i], 0, 0);
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
	u_int64_t start, end; 
	char * argv[3];
	argv[0] = "first";
	argv[1] = "second";
	argv[2] = NULL;
	double cyclesKernel[runs];
	double cyclesProcess[runs];

	struct timeval t1, t2;
	int process_thread_time, kernel_thread_time, id;

	//Create Kernel level threads 
    rdtsc();
	int i = 0;
<<<<<<< HEAD
	while(i < num_threads) {
		runKernelThread(i);
		i++;
	}
    rdtsc1();
	start = ( ((u_int64_t)cycles_high << 32) | cycles_low );
    end = ( ((u_int64_t)cycles_high1 << 32) | cycles_low1 );
	kernel_thread_time = (end - start)/(num_threads * 1.0);
	fprintf(stdout, "Kernel Thread time: %d\n", kernel_thread_time);
=======
>>>>>>> 74e22f18158d91ea650dac1bc097ee9b038342ff

	for(int r = 0; r < runs; r++) {
		while(i < num_threads) {
			runKernelThread(i);
			i++;
		}
	    rdtsc1();
		start = ( ((uint64_t)cycles_high << 32) | cycles_low );
	    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		kernel_thread_time = (end - start)/(num_threads * 1.0);
		//fprintf(stdout, "Kernel Thread time: %d\n", kernel_thread_time);
		cyclesKernel[r] = kernel_thread_time;

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
		//fprintf(stdout, "Process time: %d\n", process_thread_time);
		cyclesProcess[r] = process_thread_time;
	}
<<<<<<< HEAD
    rdtsc1();

    start = ( ((u_int64_t)cycles_high << 32) | cycles_low );
    end = ( ((u_int64_t)cycles_high1 << 32) | cycles_low1 );
	process_thread_time = (end - start)/(num_processes * 1.0);	
	fprintf(stdout, "Process time: %d\n", process_thread_time);
=======
	stdev(cyclesKernel, runs);
	stdev(cyclesProcess, runs);
>>>>>>> 74e22f18158d91ea650dac1bc097ee9b038342ff
}




