#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object create_object(int size) {
    Object obj;
    obj.size = size;
    obj.data = (int *)malloc(size * sizeof(int));
    if (obj.data != NULL) {
        for (int i = 0; i < size; i++) {
            obj.data[i] = i;
        }
    }
    return obj;
}

void release_object(Object *obj) {
    if (obj != NULL && obj->data != NULL) {
        free(obj->data);
        obj->data = NULL;
        obj->size = 0;
    }
}

int main() {
    Object obj = create_object(10);
    if (obj.data != NULL) {
        for (int i = 0; i < obj.size; i++) {
            printf("Object.data[%d]: %d\n", i, obj.data[i]);
        }
        release_object(&obj);
    } else {
        printf("Object creation failed\n");
    }
    return 0;
}