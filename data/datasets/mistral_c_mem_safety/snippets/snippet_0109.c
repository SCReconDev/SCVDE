#include <stdio.h>
#include <stdlib.h>

void create_object(int **ptr) {
    *ptr = (int *)malloc(sizeof(int));
    **ptr = 20;
}

int main() {
    int *ptr;
    create_object(&ptr);
    printf("Value: %d\n", *ptr);
    return 0;
}