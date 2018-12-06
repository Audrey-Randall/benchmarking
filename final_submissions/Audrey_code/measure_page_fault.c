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
#include "util.h"
#include <string.h>

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
  int reps = 20;
  int num_faults = 0;
  int num_min_faults = 0;
  double measurements[reps];
  char* filenames[] = {"test0.txt", "test1.txt", "test2.txt", "test3.txt",
                      "test4.txt", "test5.txt", "test6.txt", "test7.txt",
                      "test8.txt", "test9.txt", "test10.txt", "test11.txt",
                      "test12.txt", "test13.txt", "test14.txt", "test15.txt",
                      "test16.txt", "test17.txt", "test18.txt", "test19.txt"};
  for(int j = 0; j < reps; j++) {
    measurements[j] = measure_page_fault(filenames[j]);
    printf("%f\n", measurements[j]);
    getrusage(RUSAGE_SELF, &r);
	  num_faults += r.ru_majflt;
    //printf("num faults: %ld\n", r.ru_majflt);
    num_min_faults += r.ru_minflt;
  }
  printf("Total major page faults: %d\n", num_faults);
  printf("Total minor page faults: %d\n", num_min_faults);

  double stdev, avg;
  stdev_and_avg(&measurements[2], reps-2, &avg, &stdev);
  printf("Before removing outliers, avg = %f and stdev = %f\n", avg, stdev);
  strip_outliers(measurements, reps, avg, 1000);
  //printf("Standard deviation: %f Average: %f\n", stdev, avg);
}
