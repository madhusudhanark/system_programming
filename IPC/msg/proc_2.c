#include<stdio.h>
#include<fcntl.h>
#include<mqueue.h>
#include<errno.h>
#include <string.h>
#include<stdlib.h>

mqd_t mq;
#define MQ_NAME "/msgque"

int main()


{
   int ret;
   mq = mq_open(MQ_NAME,O_RDWR);
   if(mq == -1)
        {
            printf(" error in recieve open");
            mq_close(mq);
            return -1;
        }
   
    struct mq_attr attr;
    mq_getattr(mq, &attr);
//printf(" sizeof messge %ld",);

char *message = malloc(attr.mq_msgsize);
if(!message)
  printf("memory allocation failed\n");
printf(" sizeof messge %ld",attr.mq_msgsize);


   //char message[62];
   while(1)
   {
            ret = mq_receive(mq,message,8192,NULL);
        
            if(ret == -1)
            {
                printf("error in recieving %d: %s \n",errno, strerror(errno));
                mq_close(mq);
                return -1;
                printf("the message recived %s\n",message);
            }
    }
   mq_close(mq);
   return 0;
}