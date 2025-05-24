#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE 5
#define NUM_CONSUMER 2

int buffer[BUFFER_SIZE];
int in = 0 , out = 0;

sem_t full_value;
sem_t empty_value;

pthread_mutex_t mutex;

void* producer(void *args)
{
    
    int item;
    while(1){
    item = rand() % 100;
    printf("Producer: Produced item %d\n", item);
    sem_wait(&empty_value);
    pthread_mutex_lock(&mutex);
    buffer[in] = item;
    in  = (in +1 ) % BUFFER_SIZE;
    printf("Producer: Added item %d to buffer\n", item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full_value);        
    sleep(1); // Simulate time taken to produce an item
    }
  return NULL;
}

void* consumer(void *args)
{
    int id = *(int *)args;
    int item;
    while(1){
    sem_wait(&full_value);
    pthread_mutex_lock(&mutex);
    item = buffer[out];
    out  = out % BUFFER_SIZE;
    printf("Consumer %d: Consumed item %d\n", id, item);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty_value);
    }
  return NULL;
   
}

int main()
{
    pthread_t prod_thread,con_thread[NUM_CONSUMER];
    int consumer_ids[NUM_CONSUMER];

    sem_init(&empty_value,0,BUFFER_SIZE);
    sem_init(&full_value,0,0);

    pthread_create(&prod_thread,NULL,producer,NULL);

    for(int i = 0;i<NUM_CONSUMER;i++)
    {
     consumer_ids[i] = i+1; 
     pthread_create(&con_thread[i],NULL,consumer,&consumer_ids[i]);
    }

    pthread_join(prod_thread,NULL);
    for(int i = 0; i <NUM_CONSUMER;i++)
    {
      pthread_join(con_thread[i],NULL);
    }

    sem_destroy(&empty_value);
    sem_destroy(&full_value);
    pthread_mutex_destroy(&mutex);

    return 0;
}