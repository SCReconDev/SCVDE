#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Object;

Object *create_object() {
    Object *obj = (Object *)malloc(sizeof(Object));
    obj->data = (int *)malloc(sizeof(int));
    return obj;
}

int main() {
    Object *obj = create_object();
    obj->data[0] = 100;
    printf("Object data: %d\n", obj->data[0]);
    return 0;
}