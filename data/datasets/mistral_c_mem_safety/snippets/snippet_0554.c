#include <stdio.h>
#include <stdlib.h>

void manage_resource() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        printf("Value: %d\n", *ptr);
        free(ptr);
    } else {
        printf("Memory allocation failed.\n");
    }
}

int main() {
    manage_resource();
    return 0;
}