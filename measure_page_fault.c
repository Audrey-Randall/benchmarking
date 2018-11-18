#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

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

int measure_page_fault(char* filename){
  // We need to try to measure a whole page fault, from attempting to access
  // the memory address to actually being able to access it. So we need to find
  // a way to ask for a new page every time.
  // Need to flush cache
  int page_size = getpagesize();
  int k = 0;
  int start, end;

  int fd = open(filename, O_RDONLY, (mode_t)0600);
  assert(fd != -1);
  struct stat stats;
  fstat(fd, &stats);
  posix_fadvise(fd, 0, stats.st_size, POSIX_FADV_DONTNEED);
  int repetitions[stats.st_size];
  char* page = mmap(NULL, stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
  assert(page != MAP_FAILED);

  rdtsc();
  k += page[0];
  rdtsc1();
  start = ( ((uint64_t)cycles_high << 32) | cycles_low );
  end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
  close(fd);
  return end - start;
}

int main() {
  struct rusage r;
  printf("Page size: %d\n", getpagesize());
  int reps = 50;
  int num_faults = 0;
  float measurements[reps];
  for(int j = 0; j < 50; j++) {
    measurements[j] = measure_page_fault("test.txt");
    getrusage(RUSAGE_SELF, &r);
	num_faults += r.ru_majflt;
  }
  printf("Total page faults: %d\n", num_faults);
}
