#include <stdio.h>
#include <stdlib.h>

void create_object() {
    int *obj = (int *)malloc(sizeof(int));
    *obj = 42;
    printf("Object value: %d\n", *obj);
}

int main() {
    create_object();
    return 0;
}