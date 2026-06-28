#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Object;

Object create_object(size_t size) {
    Object obj;
    obj.data = (int *)malloc(size * sizeof(int));
    if (obj.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    obj.size = size;
    for (size_t i = 0; i < size; i++) {
        obj.data[i] = i * 5;
    }

    return obj;
}

void release_object(Object *obj) {
    if (obj == NULL || obj->data == NULL) {
        fprintf(stderr, "Null pointer\n");
        return;
    }

    free(obj->data);
    obj->data = NULL;
    obj->size = 0;
}

int main() {
    Object obj = create_object(10);

    for (size_t i = 0; i < obj.size; i++) {
        printf("Object[%zu]: %d\n", i, obj.data[i]);
    }

    release_object(&obj);

    return 0;
}