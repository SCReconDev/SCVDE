#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Object;

void create_object() {
    Object *obj = (Object *)malloc(sizeof(Object));
    if (obj == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    obj->value = 42;
    printf("Object value: %d\n", obj->value);
    free(obj);
}

int main() {
    create_object();
    return 0;
}