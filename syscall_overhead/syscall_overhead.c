#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <sys/syscall.h>
#include <sys/time.h>

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

int procedureCall(int i, int j) {
	return i + j;
}

int systemCall() {
	struct timespec start; 
	clock_gettime(CLOCK_MONOTONIC, &start);
	return 0;
}

int main() {
	uint64_t start, end;
	int i, j;
	long iterations = 1000000;
	long runs = 100;
	float avg_syscall, avg_procedure; 
	struct timeval t1, t2;
	double cyclesSys[runs];
	double cyclesProc[runs];


	FILE *fp1; 
	fp1 = fopen("avg_procedure.txt", "w+");
	FILE *fp2; 
	fp2 = fopen("avg_syscall.txt", "w+");

	if(fp1 == NULL || fp2 == NULL) {
		printf("File Not Found\n");
		return 0;
	}
	for(int r = 0; r < runs; r++) {
		//Calculate avg time for empty function call
    	rdtsc();
		for(int i = 0; i < iterations; i++) {
			j = procedureCall(r, r);
		}
    	rdtsc1();
    	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		avg_procedure = (end - start)/(iterations * 1.0);
		cyclesProc[r] = avg_procedure;
		fprintf(fp1, "%f\n", avg_procedure);

		//Calculate avg time for procedure call
    	rdtsc();
		for(int i = 0; i < iterations; i++) {
			j = systemCall();
		}

    	rdtsc1();
    	start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    	end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
		avg_syscall = (end - start)/(iterations * 1.0);
		cyclesSys[r] = avg_syscall;
		fprintf(fp2, "%f\n", avg_syscall);
	}
	stdev(cyclesProc, runs);
	stdev(cyclesSys, runs);

}






