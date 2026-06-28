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
    if (obj.data == NULL) {
        printf("Memory allocation failed\n");
        obj.size = 0;
    }
    return obj;
}

void release_object(Object *obj) {
    if (obj->data != NULL) {
        free(obj->data);
        obj->data = NULL;
        obj->size = 0;
    }
}

int main() {
    Object obj = create_object(10);
    if (obj.data == NULL) {
        return 1;
    }
    for (int i = 0; i < obj.size; i++) {
        obj.data[i] = i;
    }
    release_object(&obj);
    if (obj.data == NULL) {
        printf("Object released successfully\n");
    }
    return 0;
}