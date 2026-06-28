#include <stdio.h>
#include <stdlib.h>

int* create_object() {
    int *obj = (int*)malloc(sizeof(int));
    *obj = 10;
    return obj;
}

int main() {
    int *obj = create_object();
    printf("Object value: %d\n", *obj);
    return 0;
}