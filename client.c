#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include "util.h"

unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

// This function was basically taken from https://stackoverflow.com/questions/8189935/is-there-any-way-to-ping-a-specific-ip-address-with-c
// It was so simple my function looks exactly like the one posted.
void ping() {
  int pipe_ends[2];
  char buffer[1024];
  pipe(pipe_ends);

  if (fork() == 0) {
      // Duplicate the end of the pipe to stdout
      dup2(pipe_ends[1], STDOUT_FILENO);
      execl("/sbin/ping", "ping", "-c 1", "8.8.8.8", (char*)NULL);
  }
  else {
      wait(NULL);
      // Read from the reading end of the pipe into the buffer and print it
      read(pipe_ends[0], buffer, 1024);
      printf("%s\n", buffer);
  }

  close(pipe_ends[0]);
  close(pipe_ends[1]);
}

int client() {
  int sock = -1;
  struct sockaddr_in serv_addr;
  char buffer[1] = {0};
  int num_trials = 10;
  double cycles[num_trials];
  int start, end;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(9090);

  // Convert IPv4 and IPv6 addresses from text to binary form
  assert(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)>0);

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      printf("\nConnection Failed \n");
      return -1;
  }
  char* msg = ".";

  for(int i = 0; i < num_trials; i++) {
    rdtsc();
    send(sock, msg, strlen(msg), 0);
    read(sock, buffer, 1);
    rdtsc1();

    //printf("%s\n",buffer );
    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    cycles[i] = end - start;
    printf("%lf, ", cycles[i]);
  }
  double avg, stdev;
  stdev_and_avg(cycles, num_trials, &avg, &stdev);
  printf("Average: %lf, stdev: %lf\n", avg, stdev);
  return 0;
}

int main(int argc, char** argv) {
    if(argc < 2) {
      printf("Usage: ./client client or ./client ping\n");
      return 1;
    }

    if(strcmp(argv[1], "client") == 0) {
      client();
    } else if (strcmp(argv[1], "ping") == 0) {
      ping();
    }
}
