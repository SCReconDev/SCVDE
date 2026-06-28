#include <stdio.h>
#include <stdlib.h>

void manage_resources() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    *ptr = 42;
    printf("Resource managed: %d\n", *ptr);
    free(ptr);
}

int main() {
    manage_resources();
    return 0;
}