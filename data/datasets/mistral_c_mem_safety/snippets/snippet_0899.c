#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Object;

Object createObject(size_t size) {
    Object obj;
    obj.size = size;
    obj.data = (int *)malloc(size * sizeof(int));

    if (obj.data == NULL) {
        printf("Memory allocation failed.\n");
        obj.size = 0;
    }

    return obj;
}

void releaseObject(Object *obj) {
    if (obj == NULL || obj->data == NULL) {
        printf("Null object or data.\n");
        return;
    }

    free(obj->data);
    obj->data = NULL;
    obj->size = 0;
}

void useObject(Object *obj) {
    if (obj == NULL || obj->data == NULL) {
        printf("Null object or data.\n");
        return;
    }

    for (size_t i = 0; i < obj->size; i++) {
        printf("%d ", obj->data[i]);
    }
    printf("\n");
}

int main() {
    Object obj = createObject(5);

    if (obj.data == NULL) {
        printf("Failed to create object.\n");
        return 1;
    }

    for (size_t i = 0; i < obj.size; i++) {
        obj.data[i] = i;
    }

    useObject(&obj);
    releaseObject(&obj);

    return 0;
}