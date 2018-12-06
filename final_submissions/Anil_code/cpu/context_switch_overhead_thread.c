#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

uint32_t COUNTER;
pthread_mutex_t LOCK;
pthread_mutex_t START;
pthread_cond_t CONDITION;

void * threads (
    void * unused
) {
    // Wait till we may fire away
    pthread_mutex_lock(&START);
    pthread_mutex_unlock(&START);

    pthread_mutex_lock(&LOCK);
    // If I'm not the first thread, the other thread is already waiting on
    // the condition, thus Ihave to wake it up first, otherwise we'll deadlock
    if (COUNTER > 0) {
        pthread_cond_signal(&CONDITION);
    }
    for (;;) {
        COUNTER++;
        pthread_cond_wait(&CONDITION, &LOCK);
        // Always wake up the other thread before processing. The other
        // thread will not be able to do anything as long as I don't go
        // back to sleep first.
        pthread_cond_signal(&CONDITION);
    }
    pthread_mutex_unlock(&LOCK); //To unlock
}

// Rdtsc blocks
unsigned cycles_low, cycles_high;

static __inline__ unsigned long long rdtsc(void)
{
    __asm__ __volatile__ ("RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "rbx", "rcx", "rdx");
}


int main (
    int argc,
    char ** argv
) {
    pthread_t t1;
    pthread_t t2;

    pthread_mutex_init(&LOCK, NULL);
    pthread_mutex_init(&START, NULL);   
    pthread_cond_init(&CONDITION, NULL);

    pthread_mutex_lock(&START);
    COUNTER = 0;
    pthread_create(&t1, NULL, threads, NULL);
    pthread_create(&t2, NULL, threads, NULL);
    pthread_detach(t1);
    pthread_detach(t2);

    // Get start time and fire away
	rdtsc();
	uint64_t start_time_cycles = ( ((uint64_t)cycles_high << 32) | cycles_low );

    pthread_mutex_unlock(&START);
    // Wait for about a second
    sleep(1);

    // Stop both threads
    pthread_mutex_lock(&LOCK);

    // Find out how much time has really passed. sleep won't guarantee me that
    // I sleep exactly one second, I might sleep longer since even after being
    // woken up, it can take some time before I gain back CPU time. Further
    // some more time might have passed before I obtained the lock!
	rdtsc();
	uint64_t end_time_cycles = ( ((uint64_t)cycles_high << 32) | cycles_low );

    // Correct the number of thread switches accordingly
    printf("%lu %lu %lu %u\n", end_time_cycles, start_time_cycles, (end_time_cycles - start_time_cycles), COUNTER);
    printf("Average context switch time cycles for one switch is: %lf\n", (end_time_cycles - start_time_cycles)*1.0/COUNTER);


	// Write to file if provided
	if(argc > 1)
	{
		FILE *fp;

	   	fp = fopen(argv[1], "a+");
	   	fprintf(fp, "%lf\n", (end_time_cycles - start_time_cycles)*1.0/COUNTER);
	   	fclose(fp);
	}
    return 0;
}
