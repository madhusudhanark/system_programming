#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5    // Size of the shared buffer
#define NUM_CONSUMERS 3  // Number of consumer threads

int buffer[BUFFER_SIZE];
int in = 0, out = 0;     // Buffer indices for producer and consumer

sem_t empty_slots;       // Semaphore to count empty slots
sem_t full_slots;        // Semaphore to count full slots
pthread_mutex_t mutex;   // Mutex for protecting buffer access

void* producer(void* arg) {
    int item = 0;
    while (1) {
        // Produce an item
        item = rand() % 100;
        printf("Producer: Produced item %d\n", item);
        
        // Wait for an empty slot
        sem_wait(&empty_slots);
        
        // Lock the buffer and add the item
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer: Added item %d to buffer\n", item);
        pthread_mutex_unlock(&mutex);
        
        // Signal a full slot
        sem_post(&full_slots);
        
        sleep(1); // Simulate time taken to produce an item
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    int item;
    while (1) {
        // Wait for a full slot
        sem_wait(&full_slots);
        
        // Lock the buffer and remove an item
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer %d: Consumed item %d\n", id, item);
        pthread_mutex_unlock(&mutex);
        
        // Signal an empty slot
        sem_post(&empty_slots);
        
        sleep(2); // Simulate time taken to process the item
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_threads[NUM_CONSUMERS];
    int consumer_ids[NUM_CONSUMERS];
    
    // Initialize semaphores and mutex
    sem_init(&empty_slots, 0, BUFFER_SIZE);  // Initially, all slots are empty
    sem_init(&full_slots, 0, 0);             // Initially, no full slots
    pthread_mutex_init(&mutex, NULL);
    
    // Create the producer thread
    pthread_create(&prod_thread, NULL, producer, NULL);
    
    // Create the consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumer_ids[i] = i + 1;
        pthread_create(&cons_threads[i], NULL, consumer, &consumer_ids[i]);
    }
    
    // Wait for the threads (this example runs indefinitely)
    pthread_join(prod_thread, NULL);
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(cons_threads[i], NULL);
    }
    
    // Destroy semaphores and mutex (unreachable in this example)
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
