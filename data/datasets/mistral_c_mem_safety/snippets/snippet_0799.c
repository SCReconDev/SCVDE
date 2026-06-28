#include <stdio.h>

typedef struct {
    int value;
} Object;

void create_object(Object **obj) {
    *obj = (Object *)malloc(sizeof(Object));
    if (*obj != NULL) {
        (*obj)->value = 10;
    }
}

void release_object(Object *obj) {
    if (obj != NULL) {
        free(obj);
    }
}

int main() {
    Object *obj = NULL;
    create_object(&obj);
    if (obj != NULL) {
        printf("Object value: %d\n", obj->value);
        release_object(obj);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}