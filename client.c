#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>
#include <time.h>
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

void write_bandwidth_measurements(char* file, int* bytes, double* times,
                                  int len) {
  FILE *f = fopen(file, "w");
  if(f == NULL) {
    printf("Error opening %s\n", file);
    return;
  }

  for (int i = 0; i < len; i++) {
    if (times[i] == 0) break;
    fprintf(f, "%lf, %d\n", times[i], bytes[i]);
  }
  fclose(f);
}

void perform_bandwidth_measurement(int socket) {
  char buffer[1] = {0};
  int n;
  int msg_len = 100000;
  char msg[msg_len];
  int bytes_sent = 0;
  int counter = 0;
  int num_time_measurements = 0;

  int seconds_to_measure = 60;
  int measure_interval = 100;
  // When measure_interval=100, measurement code gets called approx. 75 times/sec.
  // Round up to 100 to prevent overflows.
  int result_len = 100*measure_interval*seconds_to_measure;
  int running_bytes_total[result_len];
  double times[result_len];
  memset(running_bytes_total, 0, result_len);
  memset(times, 0, result_len);

  memset(msg, 'a', msg_len);

  struct timespec start={0,0}, end={0,0};
  clock_gettime(CLOCK_MONOTONIC, &start);
  double rough_finish_time = start.tv_sec + 0.0000000001*start.tv_nsec +
                           seconds_to_measure;

  while(1) {
    n = send(socket, msg, strlen(msg), 0);
    if(n==-1) {
      perror("Broke the socket");
      break;
    }
    bytes_sent += n;
    if (!(counter%measure_interval)) {
      running_bytes_total[counter/100] = bytes_sent;
      clock_gettime(CLOCK_MONOTONIC, &end);
      num_time_measurements++;
      double rough_time = end.tv_sec + 0.0000000001*end.tv_nsec;
      //printf("Rough time: %lf\n", rough_time);
      times[counter/100] = rough_time;
      //printf("Rough time: %li\n", rough_time);
      if(rough_time > rough_finish_time) break;
    }
    counter++;
  }
  printf("Time checked in loop %d times\n", num_time_measurements);

  write_bandwidth_measurements("bandwidth_results.txt", running_bytes_total,
                                times, result_len);
}

int client_setup() {
  int sock = -1;
  struct sockaddr_in serv_addr;

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
  return sock;
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
    } else if (strcmp(argv[1], "bandwidth") == 0) {
      int sock = client_setup();
      if (sock > -1) {
        perform_bandwidth_measurement(sock);
      } else {
        printf("Error initializing client: Bandwidth measurement could not be"
        " performed.\n");
      }
    }
    return 0;
}
