#include <stdio.h>
#include <stdlib.h>

void create_resource() {
    int *resource = (int *)malloc(sizeof(int));
    *resource = 42;
    printf("Resource created with value: %d\n", *resource);
}

int main() {
    create_resource();
    return 0;
}