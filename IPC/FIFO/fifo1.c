#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>


int main()
{
  int fd;
  ssize_t ret;
  char buffer[10] = "writebuff";
  int i = 5;
  fd = open("myfifo",O_WRONLY);

  if(fd < 0)
  {
     printf(" fifo open error\n");
     return -1;
  }
  while(i > 0)
  {

      ret = write(fd,buffer,sizeof(buffer) - 1);
      if(ret == -1)
          printf("write error\n");
      sleep(1);
      i--;
  }


  //buffer[sizeof(buffer) - 1] = '\0';

  //printf(" buffer is : %s\n",buffer);

  
  
return 0;
}