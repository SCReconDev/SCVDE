#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
} Object;

Object* createObject(int size) {
    Object* obj = (Object*)malloc(sizeof(Object));

    if (obj == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    obj->size = size;
    obj->data = (int*)malloc(size * sizeof(int));

    if (obj->data == NULL) {
        printf("Memory allocation failed.\n");
        free(obj);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        obj->data[i] = i * 4;
    }

    return obj;
}

void releaseObject(Object* obj) {
    if (obj != NULL) {
        if (obj->data != NULL) {
            free(obj->data);
        }
        free(obj);
    }
}

void useObject(Object* obj) {
    if (obj == NULL || obj->data == NULL) {
        printf("Invalid object or data.\n");
        return;
    }

    for (int i = 0; i < obj->size; i++) {
        printf("Object data[%d]: %d\n", i, obj->data[i]);
    }
}

int main() {
    int size;

    printf("Enter the size of the object data: ");
    scanf("%d", &size);

    Object* obj = createObject(size);

    if (obj == NULL) {
        printf("Object creation failed.\n");
        return 1;
    }

    useObject(obj);

    releaseObject(obj);

    return 0;
}