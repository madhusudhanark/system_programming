#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
  int                socket_fd;
  int                opt = 1;
  struct sockaddr_in address;

  if (socket(AF_INET, SOCK_STREAM, 0) < 0)
  {
    perror("error in socket creation");
  };

  if (gsetsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    perror("setsokcet");
    exit(EXIT_FAILURE);
  }
  address.sin_family      = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port        = htons(PORT);
}