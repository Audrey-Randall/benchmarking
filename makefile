CC=gcc
CFLAGS=-O0 -g

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

measure_overhead: measure_overhead.o
	$(CC) -o measure_overhead measure_overhead.o
