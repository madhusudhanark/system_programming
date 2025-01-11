#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include"headers.h"

//charactor declarations
char name[20] = "madhusudhanark"; //auto terminator \0 is added here//
char village[] = "rajathadripura"; //auto terminator \0 is added here//
char Taluq[10]; // use strcpy to assign value
char *usn = "1BM12IT015"; // this is stored read only memory
const char *father = "kumar"; // this is stored read only memory
//name[] = {"M","a","d","h","u","\0"}; 
//name[20] = {"M","a","d","h","u","\0"};  both give error , should be done during init

// extern variables from other files
extern char pincode[7];

//integer variables
int x = 1;

// function declarations
static void signal_handler(int signum)
{
  printf("signal recieved from parent process SIGINT %d\n", signum);
  sleep(2);
  exit(0);
}

int main()
{
  pincode[0] = 'q';
  pincode[1] = '7';
  pincode[2] = '2';
  pincode[3] = '1';
  pincode[4] = '1';
  pincode[5] = '4';
  pincode[6] = '\0';

  pid_t pid1 ;

  pid1 = fork();
  if(pid1 < 0)
  {
    perror("failed to create ");
    exit(1);  /*due to error in creating a process*/
  }

  if(pid1 == 0)
  {
    signal(SIGINT,signal_handler);
    printf("this is inside child process : %d\n",getpid());
    while(1)
    {
      printf("waiting for recieving signals\n");
      sleep(2);
    }
    return 0;
  }
  else
  {
    printf("this is inside parent process : %d\n", getpid());
    sleep(10);
    kill(pid1,SIGTERM);
    wait(NULL);
    printf("exiting parent process\n");
  }
  return 0;
}
