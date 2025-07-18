#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


int main()
{
  int fd;
  ssize_t ret;
  char buffer[10];
  int i = 5;
  fd = open("myfifo",O_RDONLY);

  if(fd < 0)
  {
     printf(" fifo open error\n");
     return -1;
  }

  while( i > 0 )
  {

    ret = read(fd,buffer,sizeof(buffer) - 1);
        if(ret == -1)
          {printf("read error\n");
            return -1;
          }
    sleep(1);
    buffer[sizeof(buffer) - 1] = '\0';
    printf(" buffer is : %s\n",buffer);
    i--;
  }
return 0;
}