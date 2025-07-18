#include<stdio.h>
#include<linux/fs.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main()
{

   int fd;
   fd =  open("hello.txt",O_CREAT | O_RDWR | O_APPEND);
   //fd =  open("read_data.txt",O_CREAT | O_RDWR | O_APPEND,S_IRUSR | S_IRWXU);
   char buf[100];

   if(fd == -1)
      {perror("error creating file\n");
      return -1;}
    perror("error creating file\n");
    write(fd,"hello world\n",12);
    lseek(fd, 0, SEEK_SET);
     ssize_t readbytes = read(fd,buf,100);
     printf("%ld\n",readbytes);
    //buf[readbytes] = '\0';
    printf("%s\n",buf);
    close(fd);
    return 0;


}