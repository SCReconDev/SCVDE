#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Object;

Object *create_object(size_t size) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    obj->data = (int *)malloc(size * sizeof(int));
    if (obj->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(obj);
        return NULL;
    }

    obj->size = size;
    return obj;
}

void release_object(Object *obj) {
    if (obj != NULL) {
        if (obj->data != NULL) {
            free(obj->data);
        }
        free(obj);
    }
}

int main() {
    size_t size = 5;
    Object *obj = create_object(size);
    if (obj == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < obj->size; i++) {
        obj->data[i] = i * 3;
    }

    printf("Object data:\n");
    for (size_t i = 0; i < obj->size; i++) {
        printf("%d ", obj->data[i]);
    }
    printf("\n");

    release_object(obj);
    return 0;
}