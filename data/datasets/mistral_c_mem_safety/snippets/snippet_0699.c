#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Object;

Object *create_object(size_t size) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj == NULL) {
        return NULL;
    }

    obj->data = (int *)malloc(size * sizeof(int));
    if (obj->data == NULL) {
        free(obj);
        return NULL;
    }

    obj->size = size;
    return obj;
}

void release_object(Object *obj) {
    if (obj == NULL) {
        return;
    }

    free(obj->data);
    free(obj);
}

int main() {
    Object *obj = create_object(10);
    if (obj == NULL) {
        printf("Object creation failed\n");
        return 1;
    }

    printf("Object created with size %zu\n", obj->size);
    release_object(obj);
    return 0;
}