#include <stdio.h>
#include <stdlib.h>

int* create_object() {
    int *obj = malloc(sizeof(int));
    *obj = 50;
    return obj;
}

int main() {
    int *obj = create_object();
    printf("Object value: %d\n", *obj);
    return 0;
}