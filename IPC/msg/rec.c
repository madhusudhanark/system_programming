#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MQ_NAME "/msgque1"

int main() {
    mqd_t mq = mq_open(MQ_NAME, O_RDONLY);
    if (mq == -1) {
        perror("mq_open");
        return -1;
    }

    struct mq_attr attr;
    if (mq_getattr(mq, &attr) == -1) {
        perror("mq_getattr");
        mq_close(mq);
        return -1;
    }

    char *buffer = malloc(attr.mq_msgsize);
    if (!buffer) {
        perror("malloc");
        mq_close(mq);
        return -1;
    }

    ssize_t bytes_read = mq_receive(mq, buffer, attr.mq_msgsize, NULL);
    if (bytes_read == -1) {
        perror("mq_receive");
        free(buffer);
        mq_close(mq);
        return -1;
    }

    printf("Message received: %s\n", buffer);

    free(buffer);
    mq_close(mq);
    return 0;
}
