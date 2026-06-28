#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Object;

Object create_object(int size) {
    Object obj;
    obj.data = (int *)malloc(size * sizeof(int));
    obj.size = size;

    if (obj.data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        obj.size = 0;
    } else {
        for (int i = 0; i < obj.size; i++) {
            obj.data[i] = i;
        }
    }

    return obj;
}

void release_object(Object *obj) {
    if (obj == NULL || obj->data == NULL) {
        fprintf(stderr, "Invalid object\n");
        return;
    }

    free(obj->data);
    obj->data = NULL;
    obj->size = 0;
}

int main() {
    int size;

    printf("Enter size: ");
    scanf("%d", &size);

    Object obj = create_object(size);

    if (obj.data == NULL) {
        return 1;
    }

    printf("Object created\n");

    release_object(&obj);

    printf("Object released\n");

    return 0;
}