#include <stdio.h>
#include <stdlib.h>

void use_released_object() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr != NULL) {
        *ptr = 42;
        free(ptr);
        ptr = NULL;
    } else {
        printf("Memory allocation failed.\n");
    }
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Pointer is null.\n");
    }
}

int main() {
    use_released_object();
    return 0;
}