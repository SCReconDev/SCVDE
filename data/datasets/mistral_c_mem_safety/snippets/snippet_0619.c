#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Object;

Object* createObject(size_t size) {
    Object *obj = (Object*)malloc(sizeof(Object));
    if (obj != NULL) {
        obj->data = (int*)malloc(size * sizeof(int));
        if (obj->data == NULL) {
            free(obj);
            return NULL;
        }
        obj->size = size;
    }
    return obj;
}

void releaseObject(Object *obj) {
    if (obj != NULL) {
        if (obj->data != NULL) {
            free(obj->data);
        }
        free(obj);
    }
}

int main() {
    size_t size = 10;
    Object *obj = createObject(size);
    if (obj != NULL) {
        for (size_t i = 0; i < obj->size; i++) {
            obj->data[i] = i;
        }
        releaseObject(obj);
    }
    return 0;
}