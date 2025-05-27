#include<stdio.h>
#include<stdatomic.h>
#include<pthread.h>
#include<pthread.h>

typedef struct 
{
  atomic_int res_sh;
  int data;
}Shared_res;

Shared_res* create_resource(int value)
{
  Shared_res *res = malloc(sizeof(Shared_res));
  if(!res) return NULL;
  atomic_init(res->res_sh);
 

}

void aquire_resource(Shared_res *res)
{
   atomic_fetch_add(res->res_sh);
   printf("the resource has been aquired : %d\n",atomic_load(res->res_sh));
}

void release_resource(Sharedres *res)
{
 if(atomic_fetch_sub(res->res_sh) == 1)
   {
       printf("the shared value has become zero\n");
       free(res);
   } else
 {
      printf("the resource is released with ref count : %d \n",res->res_sh);
 }
}

/*copied code from copilot
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    atomic_int ref_count;
    int data;  // Simulated resource
} SharedResource;

SharedResource* create_resource(int value) {
    SharedResource* res = malloc(sizeof(SharedResource));
    if (!res) return NULL;
    atomic_init(&res->ref_count, 1);  // Initial reference
    res->data = value;
    printf("Resource created with value = %d\n", value);
    return res;
}

void acquire_resource(SharedResource* res) {
    atomic_fetch_add(&res->ref_count, 1);
    printf("Resource acquired. Ref count = %d\n", atomic_load(&res->ref_count));
}

void release_resource(SharedResource* res) {
    if (atomic_fetch_sub(&res->ref_count, 1) == 1) {
        printf("Ref count is zero. Freeing resource with value = %d\n", res->data);
        free(res);
    } else {
        printf("Resource released. Ref count = %d\n", atomic_load(&res->ref_count));
    }
}

// Simulate usage in threads
void* thread_func(void* arg) {
    SharedResource* res = (SharedResource*)arg;
    acquire_resource(res);
    sleep(1);  // Simulate work
    release_resource(res);
    return NULL;
}

int main() {
    SharedResource* res = create_resource(42);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_func, res);
    pthread_create(&t2, NULL, thread_func, res);

    // Main thread also uses the resource
    sleep(2);
    release_resource(res);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
*/
