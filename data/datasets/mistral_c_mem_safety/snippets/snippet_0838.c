#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Resource;

void manage_resource_lifecycle() {
    Resource *res = (Resource *)malloc(sizeof(Resource));
    if (res == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    res->value = 42;
    printf("Resource value: %d\n", res->value);
    free(res);
}

int main() {
    manage_resource_lifecycle();
    return 0;
}