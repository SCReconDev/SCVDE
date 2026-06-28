#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Object;

Object *create_object(int value) {
    Object *obj = (Object *)malloc(sizeof(Object));

    if (obj == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    obj->value = value;
    return obj;
}

void release_object(Object *obj) {
    if (obj != NULL) {
        free(obj);
    }
}

int main() {
    Object *obj = create_object(100);

    if (obj != NULL) {
        printf("Object value: %d\n", obj->value);
        release_object(obj);
    }

    return 0;
}