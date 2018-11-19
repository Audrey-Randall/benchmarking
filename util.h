#ifndef UTIL_H
#define UTIL_H

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

double stdev(double* vals, int len);
void stdev_and_avg(double* vals, int len, double* avg_to_fill, double* stdev_to_fill);
void strip_outliers(double* vals, int len, double avg, double tolerance);

#endif /* UTIL_H */
