#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include <fcntl.h>
#include<stdlib.h>


char *buf = "this is the buffer data to write";



int main()
{
  pid_t pid1;
  char buffer[100];
  int fd[2], temp_log;
  float temp;
  float rand_num;
  temp_log = open("file_print.txt",O_RDWR);
  setpgid(0,0);
  printf("Parent group : %d\n",getpgrp());
  

   if(pipe(fd))
     {
        perror("pipe creation failed\n");
        return -1;
     }

    pid1 = fork();
    if(pid1 == -1)
    {
        perror("error");
        return -1;
    }
       /*produce temperature*/
        if(pid1 ==  0)
        {
                close(fd[0]);
                while(1)
                    {
                        rand_num = rand();
                        write(fd[1],&rand_num,sizeof(rand_num));
                        printf("child 1 read temp : %f\n",rand_num);
                        sleep(1);
                        //close(fd[1]);
                    }
        }
        else
        {
            pid_t pid2 = fork();
            if(pid2 == -1)
            {
                printf("failed to create second child\n");
                return -1;
            }
            /*read temperature*/
            if(pid2 == 0)
            { 
                    float rand_temp;
                    close(fd[1]);
                    while(1)
                    {
                        read(fd[0],&rand_temp,sizeof(rand_temp));
                        printf("child 2 read temp : %f\n",rand_temp);
                        sleep(5);
                        //write(temp_log,&rand_temp,sizeof(rand_temp));
                    }
            }
            else
            {
                waitpid();
                waitpid();
            }
        }

   return 0;
}