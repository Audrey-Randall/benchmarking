#include <stdio.h>
#include <sys/syscall.h>
#include <sys/time.h>

int procedureCall(int i, int j) {
	return i + j;
}

int systemCall() {
	struct timespec start; 
	clock_gettime(CLOCK_MONOTONIC, &start);
	return 0;
}

long nanosec(struct timeval t) {
	return (((t.tv_sec*1000000) + t.tv_usec)*1000);
}

int main() {
	int i, j;
	long iterations = 1000000;
	long runs = 10;
	float avg_syscall, avg_procedure; 
	struct timeval t1, t2;
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
		gettimeofday(&t1, NULL);
		for(int i = 0; i < iterations; i++) {
			j = procedureCall(r, r);
		}
		gettimeofday(&t2, NULL);
		avg_procedure = (nanosec(t2) - nanosec(t1))/(iterations * 1.0);
		fprintf(fp1, "%f\n", avg_procedure );

		//Calculate avg time for procedure call
		gettimeofday(&t1, NULL);
		for(int i = 0; i < iterations; i++) {
			j = systemCall();
		}

		gettimeofday(&t2, NULL);
		avg_syscall = (nanosec(t2) - nanosec(t1))/(iterations * 1.0);
		fprintf(fp2, "%f\n", avg_syscall);
	}
}






