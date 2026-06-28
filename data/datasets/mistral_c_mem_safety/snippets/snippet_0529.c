#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object* createObject(int size) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj != NULL) {
        obj->size = size;
        obj->data = (int *)malloc(size * sizeof(int));
        if (obj->data != NULL) {
            for (int i = 0; i < size; i++) {
                obj->data[i] = i;
            }
        } else {
            free(obj);
            obj = NULL;
        }
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
    Object *obj = createObject(10);
    if (obj != NULL) {
        for (int i = 0; i < obj->size; i++) {
            printf("%d ", obj->data[i]);
        }
        printf("\n");
        releaseObject(obj);
    } else {
        printf("Object creation failed\n");
    }
    return 0;
}