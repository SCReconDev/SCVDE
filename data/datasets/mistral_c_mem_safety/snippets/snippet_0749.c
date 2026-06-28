#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object *create_object(int size) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj != NULL) {
        obj->size = size;
        obj->data = (int *)malloc(size * sizeof(int));
        if (obj->data != NULL) {
            for (int i = 0; i < size; i++) {
                obj->data[i] = i;
            }
        } else {
            free(obj);
            obj = NULL;
        }
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
    if (obj != NULL) {
        printf("Object created and initialized\n");
        release_object(obj);
    } else {
        printf("Object creation failed\n");
    }
    return 0;
}