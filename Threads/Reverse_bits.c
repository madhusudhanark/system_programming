#include <stdio.h>
#include <stdlib.h>


void modifyPointerSingle(int *ptr)
 {
    // Allocate memory to ptr (this only changes the local copy of ptr)
    printf("ptr in function before : - %p\n",ptr);  // This will be printed
    ptr = (int *)malloc(4*sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;  // Set value at the new memory location
    }
    printf("ptr in function after : - %p  *p : - %d\n",ptr,*ptr);  // This will be printed
}

int main() {
    int *p = NULL;  // Original pointer in main
    modifyPointerSingle(p);  // Pass p by value
    if (p == NULL) {
        printf("p is still NULL in main : - %p\n",p);  // This will be printed
    }
    return 0;
}
