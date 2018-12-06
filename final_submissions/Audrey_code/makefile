CC=gcc
CFLAGS=-O0 -g

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

measure_overhead: measure_overhead.o
	$(CC) -o measure_overhead measure_overhead.o -lm

server: server.o
	$(CC) -o server server.o -lm

client: client.o util.o util.h
	$(CC) -o client util.o client.o -lm

page_fault: measure_page_fault.o util.o util.h
	$(CC) -o page_fault util.o measure_page_fault.o -lm

util.o: util.c util.h
		$(CC) -c util.c

#To run:  sudo nice --20 taskset 0x1 ./<executable>
