#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


int N = 50;
int n = 1;
pthread_mutex_t mutex;
//pthread_mutex_t mutex;

void* even(void* arg){

    while(1){
    pthread_mutex_lock(&mutex);
    if( n > N){
        pthread_mutex_unlock(&mutex);
        break;
    }
    if(n % 2 == 0 ){
        printf("the even number is %d\n",n);
        n++;
    }
    pthread_mutex_unlock(&mutex);
    usleep(100);
    }
    return NULL;

}

void* odd(void* arg)
{
    
    while(1){
    pthread_mutex_lock(&mutex);
    if( n > N){

        pthread_mutex_unlock(&mutex);
        break;
    }
    if((n % 2 != 0 ))
    {
      printf("the odd number is %d\n",n);
      n++;
    }
    pthread_mutex_unlock(&mutex);
    usleep(10);
    }

    return NULL;
}


int main()
{
    pthread_t thread1,thread2;
    //pthread_mutex_init(&mutex,NULL);
    pthread_create(&thread1,NULL,even,NULL);
    pthread_create(&thread2,NULL,odd,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    //pthread_mutex_destroy(&mutex);
    return 0;
}