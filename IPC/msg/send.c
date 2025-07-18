#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MQ_NAME "/msgque1"

int main() {
    mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_WRONLY, 0644, NULL);
    if (mq == -1) {
        perror("mq_open");
        return -1;
    }

    const char *message = "Hello from sender!";
    if (mq_send(mq, message, strlen(message) + 1, 0) == -1) {
        perror("mq_send");
        mq_close(mq);
        return -1;
    }

    printf("Message sent: %s\n", message);
    mq_close(mq);
    return 0;
}
