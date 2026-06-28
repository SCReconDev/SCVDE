#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Object;

Object *create_object(size_t size) {
    Object *obj = (Object *)malloc(sizeof(Object));

    if (obj == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    obj->data = (int *)malloc(sizeof(int) * size);

    if (obj->data == NULL) {
        printf("Memory allocation failed\n");
        free(obj);
        return NULL;
    }

    obj->size = size;

    for (size_t i = 0; i < obj->size; i++) {
        obj->data[i] = i;
    }

    return obj;
}

void release_object(Object *obj) {
    if (obj == NULL) {
        printf("Null object\n");
        return;
    }

    if (obj->data != NULL) {
        free(obj->data);
    }

    free(obj);
}

int main() {
    Object *obj = create_object(10);

    if (obj == NULL) {
        printf("Object creation failed\n");
        return 1;
    }

    printf("Object created\n");
    release_object(obj);
    printf("Object released\n");
    return 0;
}