#include <stdio.h>
#include <stdlib.h>

void create_object() {
    int *obj = (int *)malloc(sizeof(int));
    *obj = 42;
    printf("Object created with value %d\n", *obj);
}

int main() {
    create_object();
    printf("Object created and used\n");
    return 0;
}