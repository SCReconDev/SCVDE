#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Object;

Object* create_object(size_t size) {
    Object* obj = (Object*)malloc(sizeof(Object));

    if (obj == NULL) {
        printf("Object creation failed\n");
        return NULL;
    }

    obj->size = size;
    obj->data = (int*)malloc(size * sizeof(int));

    if (obj->data == NULL) {
        printf("Data allocation failed\n");
        free(obj);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        obj->data[i] = i;
    }

    return obj;
}

void release_object(Object* obj) {
    if (obj != NULL) {
        if (obj->data != NULL) {
            free(obj->data);
        }
        free(obj);
    }
}

int main() {
    Object* obj = create_object(5);

    if (obj == NULL) {
        return 1;
    }

    for (size_t i = 0; i < obj->size; i++) {
        printf("Data at index %zu: %d\n", i, obj->data[i]);
    }

    release_object(obj);

    return 0;
}