CC=gcc
CFLAGS=-O0 -g

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

measure_overhead: measure_overhead.o
	$(CC) -o measure_overhead measure_overhead.o -lm

#To run:  sudo nice --20 taskset 0x1 ./measure_overhead
