#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

Resource create_resource(int size) {
    Resource res;
    res.data = (int*) malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        res.data[i] = i;
    }
    return res;
}

int main() {
    Resource res = create_resource(10);
    printf("Value: %d\n", res.data[0]);
    return 0;
}