#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object createObject(int size) {
    Object obj;
    obj.size = size;
    obj.data = (int *)malloc(size * sizeof(int));
    if (obj.data == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        obj.data[i] = i;
    }
    return obj;
}

void releaseObject(Object *obj) {
    if (obj->data != NULL) {
        free(obj->data);
        obj->data = NULL;
    }
}

void printObject(Object *obj) {
    if (obj->data == NULL) {
        printf("Object not initialized\n");
        return;
    }
    for (int i = 0; i < obj->size; i++) {
        printf("%d ", obj->data[i]);
    }
    printf("\n");
}

int main() {
    Object obj = createObject(5);
    printObject(&obj);
    releaseObject(&obj);
    printObject(&obj);
    return 0;
}