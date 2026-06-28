#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object *create_object(int size) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    obj->size = size;
    obj->data = (int *)malloc(size * sizeof(int));
    if (obj->data == NULL) {
        printf("Memory allocation failed\n");
        free(obj);
        return NULL;
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

void use_object(Object *obj) {
    if (obj == NULL || obj->data == NULL) {
        printf("Invalid object\n");
        return;
    }
    for (int i = 0; i < obj->size; i++) {
        printf("Data[%d]: %d\n", i, obj->data[i]);
    }
}

int main() {
    Object *obj = create_object(5);
    if (obj == NULL) {
        return 1;
    }
    for (int i = 0; i < obj->size; i++) {
        obj->data[i] = i;
    }
    use_object(obj);
    release_object(obj);
    return 0;
}