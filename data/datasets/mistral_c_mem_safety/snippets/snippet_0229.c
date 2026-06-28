#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
} Resource;

Resource* create_resource(int size) {
    Resource* res = (Resource*)malloc(sizeof(Resource));
    res->data = (int*)malloc(size * sizeof(int));
    return res;
}

int main() {
    Resource* res = create_resource(10);
    for (int i = 0; i < 10; i++) {
        res->data[i] = i;
    }
    return 0;
}