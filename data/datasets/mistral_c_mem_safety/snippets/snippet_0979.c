#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object *create_object(int size) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    obj->size = size;
    obj->data = (int *)malloc(size * sizeof(int));
    if (obj->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(obj);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        obj->data[i] = i;
    }
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
    Object *obj = create_object(10);
    if (obj == NULL) {
        return 1;
    }
    printf("Object created\n");
    release_object(obj);
    printf("Object released\n");
    return 0;
}