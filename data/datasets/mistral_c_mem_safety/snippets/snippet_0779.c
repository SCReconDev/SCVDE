#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
} Object;

Object* create_object(size_t size) {
    Object* obj = malloc(sizeof(Object));
    if (obj == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    obj->data = malloc(size);
    if (obj->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(obj);
        return NULL;
    }
    obj->size = size;
    return obj;
}

void release_object(Object* obj) {
    if (obj != NULL) {
        if (obj->data != NULL) {
            free(obj->data);
        }
        free(obj);
    }
}

int main() {
    Object* obj = create_object(1024);
    if (obj != NULL) {
        printf("Object created successfully\n");
        release_object(obj);
    }
    return 0;
}