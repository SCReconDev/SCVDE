#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    }
    *ptr = 10;
    printf("Value: %d\n", *ptr);
    free(ptr);
    return 0;
}