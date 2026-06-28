#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Object;

Object* create_object() {
    Object *obj = (Object*)malloc(sizeof(Object));
    obj->data = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        obj->data[i] = i;
    }
    return obj;
}

int main() {
    Object *obj = create_object();
    printf("Value: %d\n", obj->data[0]);
    return 0;
}