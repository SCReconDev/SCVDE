#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
} Resource;

Resource create_resource(int value) {
    Resource res;
    res.data = (int *)malloc(sizeof(int));
    *res.data = value;
    return res;
}

int main() {
    Resource res = create_resource(42);
    printf("Resource data: %d\n", *res.data);
    return 0;
}