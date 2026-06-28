#include <stdio.h>
#include <stdlib.h>

void create_object(int **obj) {
    *obj = (int *)malloc(sizeof(int));
    **obj = 42;
}

int main() {
    int *obj;
    create_object(&obj);
    printf("Object created with value: %d\n", *obj);
    return 0;
}