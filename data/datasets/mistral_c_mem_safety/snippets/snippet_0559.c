#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Object;

Object* create_object() {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj != NULL) {
        obj->value = 42;
    }
    return obj;
}

void release_object(Object *obj) {
    if (obj != NULL) {
        free(obj);
    }
}

int main() {
    Object *obj = create_object();
    if (obj != NULL) {
        printf("Object value: %d\n", obj->value);
        release_object(obj);
    } else {
        printf("Object creation failed.\n");
    }
    return 0;
}