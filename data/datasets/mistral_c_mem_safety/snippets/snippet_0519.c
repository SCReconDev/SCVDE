#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Object;

Object* create_object(size_t size) {
    Object* obj = (Object*)malloc(sizeof(Object));
    if (obj != NULL) {
        obj->size = size;
        obj->data = (int*)malloc(size * sizeof(int));
        if (obj->data == NULL) {
            free(obj);
            return NULL;
        }
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
    if (obj != NULL) {
        for (size_t i = 0; i < obj->size; i++) {
            obj->data[i] = i * 2;
        }
        release_object(obj);
    }
    return 0;
}