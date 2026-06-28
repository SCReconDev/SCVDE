#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Object;

Object* create_object(size_t size) {
    Object* obj = (Object*)malloc(sizeof(Object));
    if (obj == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    obj->data = (int*)malloc(size * sizeof(int));
    if (obj->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(obj);
        exit(EXIT_FAILURE);
    }

    obj->size = size;

    return obj;
}

void release_object(Object* obj) {
    if (obj != NULL) {
        free(obj->data);
        free(obj);
    }
}

int main() {
    Object* obj = create_object(10);

    for (size_t i = 0; i < obj->size; i++) {
        obj->data[i] = i;
    }

    for (size_t i = 0; i < obj->size; i++) {
        printf("%d ", obj->data[i]);
    }
    printf("\n");

    release_object(obj);

    return 0;
}