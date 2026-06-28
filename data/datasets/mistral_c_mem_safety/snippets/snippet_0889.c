#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Object;

Object* create_object() {
    Object *obj = (Object *)malloc(sizeof(Object));

    if (obj == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    obj->value = 42;
    return obj;
}

int main() {
    Object *obj = create_object();

    if (obj != NULL) {
        printf("Object value: %d\n", obj->value);
        free(obj);
    }

    return 0;
}