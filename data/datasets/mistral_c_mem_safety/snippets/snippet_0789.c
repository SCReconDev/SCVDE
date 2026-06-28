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
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        obj.data[i] = i;
    }
    return obj;
}

void release_object(Object *obj) {
    if (obj->data != NULL) {
        free(obj->data);
        obj->data = NULL;
    }
}

int main() {
    Object obj = create_object(10);
    for (int i = 0; i < obj.size; i++) {
        printf("%d ", obj.data[i]);
    }
    printf("\n");
    release_object(&obj);
    return 0;
}