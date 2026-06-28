#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

Resource create_resource(int size) {
    Resource res;
    res.data = (int *)malloc(size * sizeof(int));
    return res;
}

int main() {
    Resource res = create_resource(10);
    return 0;
}