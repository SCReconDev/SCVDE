#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Object;

Object* create_object(size_t size) {
    Object* obj = malloc(sizeof(Object));
    if (obj != NULL) {
        obj->data = malloc(size * sizeof(int));
        if (obj->data == NULL) {
            free(obj);
            return NULL;
        }
        obj->size = size;
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
    Object* obj = create_object(100);
    if (obj != NULL) {
        release_object(obj);
    }
    return 0;
}