#include <stdio.h>
#include <pthread.h>
#include<unistd.h>
#include<.h>

#define NUM_THREADS 4

typedef struct {
    unsigned char byte;
    unsigned char reversed;
    int index;
} ThreadData;

void* reverseByte(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    unsigned char b = data->byte;
    unsigned char r = 0;
    for (int i = 0; i < 8; i++) {
        r <<= 1;
        r |= (b & 1);
        b >>= 1;
    }
    data->reversed = r;
    return NULL;
}

unsigned int reverseBitsParallel(unsigned int n) {
    pthread_t threads[NUM_THREADS];
    ThreadData data[NUM_THREADS];

    // Split into 4 bytes
    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].byte = (n >> (i * 8)) & 0xFF;
        data[i].index = i;
        pthread_create(&threads[i], NULL, reverseByte, &data[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Combine reversed bytes in reverse order
    unsigned int result = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        result |= (data[i].reversed << ((NUM_THREADS - 1 - i) * 8));
    }

    return result;
}

int main() {
    unsigned int num = 25;
    pid_t pid = fork();
    if(pid < 0)
    {
     printf("child creation failed\n");
     exit(1);
    }else if(pid == 0)
    {
        printf("from child process%d\n",getpid());

    }else
    {

        printf("from parent process\n");
    }
    unsigned int reversed = reverseBitsParallel(num);
    printf("Original: %u\n", num);
    printf("Reversed: %u\n", reversed);
    return 0;
}
