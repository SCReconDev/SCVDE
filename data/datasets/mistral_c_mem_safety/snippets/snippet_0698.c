#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Resource;

void use_resource(Resource *res) {
    if (res == NULL) {
        printf("Null resource\n");
        return;
    }

    printf("Resource value: %d\n", res->value);
}

int main() {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    if (res == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    res->value = 42;
    use_resource(res);
    free(res);
    use_resource(res);
    return 0;
}