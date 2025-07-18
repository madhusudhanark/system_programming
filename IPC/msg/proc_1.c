#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#this line is added from main branch
#define MQ_NAME "/msgque"

int main() {
    mqd_t mq;
    struct mq_attr attr;



    mq = mq_open(MQ_NAME, O_RDWR | O_CREAT, 0644, &attr);
    mq_getattr(mq,);
        if (mq == -1) {
        perror("mq_open");
        return -1;
    }

    printf("mqd_t: %d\n", mq);

    char *message = malloc()
    printf("Size of message: %ld\n", strlen(message) + 1);
while(1)
{
    int ret = mq_send(mq, message, strlen(message) + 1, 0);
    if (ret == -1) {
        perror("mq_send error; retry");
        mq_close(mq);
        return -1;
    }
    strcpy(message,"this is strange world");
    sleep(1);
  }

    printf("Message sent successfully.\n");
    mq_close(mq);
    return 0;
}
