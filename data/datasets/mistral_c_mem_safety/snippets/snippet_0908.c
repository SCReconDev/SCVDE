#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Resource;

void release_resource(Resource *res) {
    if (res != NULL) {
        free(res);
        printf("Resource released\n");
    } else {
        printf("Null resource\n");
    }
}

int main() {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    if (res != NULL) {
        res->value = 42;
        printf("Resource value: %d\n", res->value);
        release_resource(res);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}