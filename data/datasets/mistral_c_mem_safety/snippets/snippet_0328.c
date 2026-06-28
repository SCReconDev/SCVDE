#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} MyObject;

void release_object(MyObject *obj) {
    free(obj);
}

int main() {
    MyObject *obj = (MyObject*) malloc(sizeof(MyObject));
    obj->value = 42;
    release_object(obj);
    printf("Object value: %d\n", obj->value);
    return 0;
}