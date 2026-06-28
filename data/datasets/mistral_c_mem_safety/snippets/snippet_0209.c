#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Object;

Object *create_object() {
    Object *obj = (Object *)malloc(sizeof(Object));
    obj->data = (int *)malloc(sizeof(int));
    *obj->data = 42;
    return obj;
}

int main() {
    Object *obj = create_object();
    printf("Object data: %d\n", *obj->data);
    return 0;
}