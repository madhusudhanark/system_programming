#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int y;

typedef struct {
    int *subarray;
    int size;
    int *result;
} ThreadArgs;

// Thread function to calculate the sum of a sub-array
void* compute_subarray_sum(void* args) {
    ThreadArgs* data = (ThreadArgs*)args;
    int sum = 0;
    for (int i = 0; i < data->size; i++) {
        sum += data->subarray[i];
    }
    *(data->result) = sum;  // Store the result in the result array
    printf(" added sum %d\n",sum);
    pthread_exit(NULL);
}

// Function to split array into subarrays of chunk_size
int** split_array(int *array, int array_size, int chunk_size, int *num_parts, int *subarray_sizes) {
    // Calculate the number of parts needed
    *num_parts = (array_size + chunk_size - 1) / chunk_size;

    int **subarrays = (int**)malloc(*num_parts * sizeof(int*));
    int index = 0;

    for (int i = 0; i < *num_parts; i++) {
        // Determine the size of each part
        int current_part_size = (i == *num_parts - 1 && array_size % chunk_size != 0) 
                                ? array_size % chunk_size 
                                : chunk_size;
        subarray_sizes[i] = current_part_size;

        // Allocate sub-array for each part
        subarrays[i] = (int*)malloc(current_part_size * sizeof(int));

        // Copy elements from the main array to the sub-array
        for (int j = 0; j < current_part_size; j++) {
            subarrays[i][j] = array[index++];
        }
    }
    return subarrays;
}

int main() {
    int array_size = 20;
    int chunk_size = 5;
    int num_parts;

    // Initialize the large array with some values
    int *array = (int*)malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        array[i] = i + 1;
    }

    // Calculate the number of parts and allocate array for subarray sizes
    num_parts = (array_size + chunk_size - 1) / chunk_size;
    int *subarray_sizes = (int*)malloc(num_parts * sizeof(int));

    // Split the large array into subarrays and calculate the number of parts
    int **subarrays = split_array(array, array_size, chunk_size, &num_parts, subarray_sizes);

    // Array to store the sum of each subarray
    int *subarray_sums = (int*)malloc(num_parts * sizeof(int));
    
    // Create an array of threads
    pthread_t *threads = (pthread_t*)malloc(num_parts * sizeof(pthread_t));
    ThreadArgs *thread_args = (ThreadArgs*)malloc(num_parts * sizeof(ThreadArgs));

    // Create threads to calculate the sum of each subarray
    for (int i = 0; i < num_parts; i++) 
    {
        thread_args[i].subarray = subarrays[i];
        thread_args[i].size = subarray_sizes[i];
        thread_args[i].result = &subarray_sums[i];
        pthread_create(&threads[i], NULL, compute_subarray_sum, &thread_args[i]);
    }

    // Wait for all threadsclear to complete
    for (int i = 0; i < num_parts; i++) {
        pthread_join(threads[i], NULL);
    }

    // Calculate the total sum by summing each subarray's sum
    int total_sum = 0;
    for (int i = 0; i < num_parts; i++) {
        total_sum += subarray_sums[i];
    }

    // Print the results
    printf("Original array:\n");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\nSubarray sums:\n");
    for (int i = 0; i < num_parts; i++) {
        printf("Sum of subarray %d: %d\n", i + 1, subarray_sums[i]);
    }
    printf("\nTotal sum of array: %d\n", total_sum);

    // Free allocated memory
    for (int i = 0; i < num_parts; i++) {
        free(subarrays[i]);
    }
    free(subarrays);
    free(subarray_sizes);
    free(subarray_sums);
    free(array);
    free(threads);
    free(thread_args);

    return 0;
}
