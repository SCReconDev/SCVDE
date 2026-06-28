#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Object;

Object* create_object(size_t size) {
    Object* obj = (Object*)malloc(sizeof(Object));

    if (obj == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    obj->data = (int*)malloc(size * sizeof(int));

    if (obj->data == NULL) {
        printf("Memory allocation failed\n");
        free(obj);
        return NULL;
    }

    obj->size = size;

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

void use_object(Object* obj) {
    if (obj == NULL || obj->data == NULL) {
        printf("Object not initialized\n");
        return;
    }

    for (size_t i = 0; i < obj->size; i++) {
        printf("Object data at index %zu: %d\n", i, obj->data[i]);
    }
}

int main() {
    Object* obj = create_object(5);

    if (obj == NULL) {
        printf("Object creation failed\n");
        return 1;
    }

    use_object(obj);
    release_object(obj);

    return 0;
}