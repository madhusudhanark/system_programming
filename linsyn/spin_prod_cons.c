/******************************************************************************

this program is to demonstrate 2 producers thread and 2 

*******************************************************************************/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif

#ifdef BUFFER_SIZE
#define NUM_PRODUCER 2
#endif
#if NUM_PRODUCER == 2
#define NUM_CONSUMER 2
#endif

#define NUM_ITEMS 5

long long buffer[BUFFER_SIZE];
pthread_spinlock_t  lock;
unsigned int count;


void* producer(void* arg)
{
    int id  = *(int*)arg;
    for(int i = 0;i < NUM_ITEMS ;i++)
    {
        while(1)
        {
                pthread_spin_lock(&lock);
                if(count < BUFFER_SIZE)
                {
                    buffer[count++] = i;
                    printf("producer name: %d each threads : Produced %d buffer count %d\n",id,i+1,count);
                    pthread_spin_unlock(&lock);
                    break;
                }
                pthread_spin_unlock(&lock);
                usleep(100);
        }

      usleep(rand() % 150000); // Simulate work
    }
    return NULL;
}

void* consumer(void*arg)
{
    int id  = *(int*)arg;
    for(int i = 0; i < NUM_ITEMS;i++)
    {
        
        while(1)
        {
            pthread_spin_lock(&lock);
            if(count > 0)
            {
                int buff = buffer[count--];
                printf("consumer %d consumed %d buffer count %d\n",id,buff+1,count);
                pthread_spin_unlock(&lock);
                break;
            }
            pthread_spin_unlock(&lock);
            usleep(100);
        }
        usleep(rand() % 150000);
    }
    return NULL;
}


int main()
{
    printf("size of buffer element %ld\n",sizeof(buffer[0]));
    pthread_t producers[NUM_PRODUCER],consumers[NUM_CONSUMER];
    int ids[NUM_PRODUCER > NUM_CONSUMER?NUM_PRODUCER:NUM_CONSUMER];
    
    pthread_spin_init(&lock,PTHREAD_PROCESS_PRIVATE);
    



    
    for(int i = 0;i< NUM_PRODUCER;i++)
    {
        ids[i] = i+1;
        pthread_create(&producers[i],NULL,&producer,&ids[i]);
    }
    
    for(int j = 0;j < NUM_CONSUMER;j++)
    {
        ids[j] = j+1;
        pthread_create(&consumers[j],NULL,&consumer,&ids[j]);
    }
    
    for(int k = 0;k< NUM_PRODUCER;k++)
    {
        pthread_join(producers[k],NULL);
    }
    
    for(int l = 0;l< NUM_CONSUMER;l++)
    {
        pthread_join(consumers[l],NULL);
    }
    
    pthread_spin_destroy(&lock);
    
    return 0;
}
