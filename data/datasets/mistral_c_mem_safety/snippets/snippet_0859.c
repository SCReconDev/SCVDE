#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Object;

Object create_object(size_t size) {
    Object obj;
    obj.size = size;
    obj.data = (int *)malloc(size * sizeof(int));
    if (obj.data != NULL) {
        for (size_t i = 0; i < size; i++) {
            obj.data[i] = i;
        }
    }
    return obj;
}

void release_object(Object *obj) {
    if (obj != NULL && obj->data != NULL) {
        free(obj->data);
        obj->data = NULL;
    }
}

int main() {
    Object obj = create_object(10);
    if (obj.data != NULL) {
        for (size_t i = 0; i < obj.size; i++) {
            printf("Element %zu: %d\n", i, obj.data[i]);
        }
        release_object(&obj);
    }
    return 0;
}