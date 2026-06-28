#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

void releaseResource(Resource *res) {
    if (res->data != NULL) {
        free(res->data);
        res->data = NULL;
    }
}

int main() {
    Resource res;
    res.size = 10;
    res.data = (int *)malloc(res.size * sizeof(int));
    if (res.data != NULL) {
        for (int i = 0; i < res.size; i++) {
            res.data[i] = i;
        }
        for (int i = 0; i < res.size; i++) {
            printf("%d ", res.data[i]);
        }
        printf("\n");
        releaseResource(&res);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}