#include <stdio.h>
#include <stdlib.h>

void create_object(int **ptr) {
    *ptr = (int *)malloc(sizeof(int));
    **ptr = 42;
}

int main() {
    int *obj;
    create_object(&obj);
    printf("Object value: %d\n", *obj);
    return 0;
}