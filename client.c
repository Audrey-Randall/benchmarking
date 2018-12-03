#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include "util.h"

unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

int ping(int trials){
  int start, end;
  double cycles[trials];
  printf("Starting ping...\n");

  for (int i = 0; i < trials; i++) {
    int failed;

    rdtsc();
    failed = system("ping -c 1 137.110.222.3 > /dev/null");
    rdtsc1();

    if (failed) printf("Ping failed\n");
    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    cycles[i] = end - start;
  }
  double avg, stdev;
  stdev_and_avg(cycles, trials, &avg, &stdev);
  printf("Average: %lf, stdev: %lf\n", avg, stdev);
}

void check_system_overhead(int num_trials) {
  int shell_available;
  int start, end;
  double cycles[num_trials];
  printf("Starting system overhead check...\n");

  for(int i = 0; i < num_trials; i++) {
    rdtsc();
    shell_available = system(NULL);
    rdtsc1();

    if (!shell_available) printf("Shell not available\n");
    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    cycles[i] = end - start;
  }
  double avg, stdev;
  stdev_and_avg(cycles, num_trials, &avg, &stdev);
  printf("Average: %lf, stdev: %lf\n", avg, stdev);
}

int client(int num_trials) {
  int sock = -1;
  struct sockaddr_in serv_addr;
  char buffer[1] = {0};
  double cycles[num_trials];
  int start, end;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  assert(sock >= 0);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(9090);

  // Convert IPv4 and IPv6 addresses from text to binary form
  assert(inet_pton(AF_INET, "137.110.222.3", &serv_addr.sin_addr)>0);

  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      printf("\nConnection Failed \n");
      return -1;
  }
  //char* msg = ".";

  for(int i = 0; i < num_trials; i++) {
    char msg[3];
    sprintf(msg, "%d", i);
    int n;
    rdtsc();
    n = send(sock, msg, strlen(msg), 0);
    read(sock, buffer, 1);
    rdtsc1();
    //printf("Bytes read: %d\n", n);

    //printf("%s\n",buffer );
    start = ( ((uint64_t)cycles_high << 32) | cycles_low );
    end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    cycles[i] = end - start;
    //printf("%lf, ", cycles[i]);
  }
  double avg, stdev;
  stdev_and_avg(cycles, num_trials, &avg, &stdev);
  printf("Average: %lf, stdev: %lf\n", avg, stdev);
  return 0;
}

int main(int argc, char** argv) {
    if(argc < 2) {
      printf("Usage: ./client <ping> or <client>\n");
      return 1;
    }

    int trials = 500;

    if(strcmp(argv[1], "client") == 0) {
      client(trials);
    } else if (strcmp(argv[1], "ping") == 0) {
      check_system_overhead(trials);
      ping(trials);
    }
    return 0;
}
