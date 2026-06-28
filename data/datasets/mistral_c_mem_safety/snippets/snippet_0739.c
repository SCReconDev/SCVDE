#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object *create_object(int size) {
    Object *object = (Object *)malloc(sizeof(Object));
    if (object == NULL) {
        printf("Object creation failed\n");
        exit(EXIT_FAILURE);
    }
    object->data = (int *)malloc(size * sizeof(int));
    if (object->data == NULL) {
        printf("Data allocation failed\n");
        free(object);
        exit(EXIT_FAILURE);
    }
    object->size = size;
    return object;
}

void release_object(Object *object) {
    if (object != NULL) {
        if (object->data != NULL) {
            free(object->data);
        }
        free(object);
    }
}

int main() {
    Object *object = create_object(10);
    printf("Object created\n");
    release_object(object);
    return 0;
}