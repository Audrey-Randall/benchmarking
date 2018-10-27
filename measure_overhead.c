#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>

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

int roll();
int unroll();

int main()
{
  uint64_t start, end;
  int i, x;
  int max_trials = 1000000;
  double roll_avg = 0.0;
  double unroll_avg = 0.0;
  for (i=0; i<max_trials; i++) {
    rdtsc();
    x = roll(1);
    rdtsc1();

    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    roll_avg += end - start;

    rdtsc();
    x = unroll(1);
    rdtsc1();

    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    unroll_avg += end - start;
  }
  printf("Rolled loop: %lf cycles\n", roll_avg*1.0/max_trials);
  printf("Unrolled loop: %lf cycles\n", unroll_avg*1.0/max_trials);
  return x;
}

int roll(int j) {
  int i;
  for(i = 0; i < 100; i+=j) {}
  return i;
}

int unroll(int j) {
  int i = 0;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  i+=j;
  return i;
}
