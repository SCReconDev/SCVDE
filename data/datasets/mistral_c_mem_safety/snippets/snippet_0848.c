#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} MyObject;

void use_object() {
    MyObject *obj = (MyObject *)malloc(sizeof(MyObject));

    if (obj == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    obj->value = 42;
    printf("Object value: %d\n", obj->value);

    free(obj);
}

int main() {
    use_object();
    return 0;
}