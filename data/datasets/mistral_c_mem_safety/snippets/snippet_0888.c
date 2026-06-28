#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Resource;

void reuse_resource(Resource *res) {
    if (res == NULL) {
        fprintf(stderr, "Null resource\n");
        return;
    }

    printf("Resource value: %d\n", res->value);
}

int main() {
    Resource *res = (Resource *)malloc(sizeof(Resource));

    if (res == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    res->value = 42;
    reuse_resource(res);

    free(res);
    reuse_resource(res);

    return 0;
}