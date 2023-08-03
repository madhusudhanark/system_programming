#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const *argv[])
{
  int socket_fd;

  if (socket(AF_INET, SOCK_STREAM, 0) < 0)
  {
    perror("error in socket creation");
  };

  if (getsockopt())
}