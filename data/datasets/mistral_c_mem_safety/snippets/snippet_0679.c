#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object *create_object(int size) {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj == NULL) {
        return NULL;
    }

    obj->data = (int *)malloc(size * sizeof(int));
    if (obj->data == NULL) {
        free(obj);
        return NULL;
    }

    obj->size = size;

    for (int i = 0; i < size; i++) {
        obj->data[i] = i * 4;
    }

    return obj;
}

void release_object(Object *obj) {
    if (obj != NULL) {
        if (obj->data != NULL) {
            free(obj->data);
        }
        free(obj);
    }
}

void use_object(Object *obj) {
    if (obj == NULL || obj->data == NULL) {
        printf("Invalid object\n");
        return;
    }

    for (int i = 0; i < obj->size; i++) {
        printf("Data[%d]: %d\n", i, obj->data[i]);
    }
}

int main() {
    int size;
    printf("Enter size: ");
    scanf("%d", &size);

    Object *obj = create_object(size);
    if (obj == NULL) {
        printf("Object creation failed\n");
        return 1;
    }

    use_object(obj);
    release_object(obj);

    return 0;
}