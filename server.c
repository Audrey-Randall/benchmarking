#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>

int main(int argc, char** argv) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  assert(socket_fd != 0);
  char* resp = ".";

  assert(!setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(9090);

  assert(bind(socket_fd, (struct sockaddr *)&address, sizeof(address))>=0);
  assert(listen(socket_fd, 3) >= 0);

  int acceptor_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
  assert(acceptor_socket >= 0);

  while(1) {
    char buffer[64000] = {0};
    int bytes_read = read(acceptor_socket , buffer, 64000);
    printf("Buffer: %s\n", buffer);
	if (bytes_read == 0) {
		break;
	}
	if (buffer[0] == 'r') {
		// Client is performing rtt measurement
    	send(acceptor_socket, resp, strlen(resp), 0);
	} else if (buffer[0] == 's') {
		// Client is performing setup and teardown measurement
		// Wait for client to shut down socket (don't shut it down too early or the
		// client's measurement will be off)
		nanosleep((const struct timespec[]){{0, 2500000L}}, NULL);
		close(acceptor_socket);
		acceptor_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
  		assert(acceptor_socket >= 0);

	}
    //printf(".");
  }
  return 0;
}
