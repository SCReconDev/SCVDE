#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Resource;

Resource* createResource(int size) {
    if (size <= 0) {
        printf("Invalid size.\n");
        return NULL;
    }
    Resource *res = (Resource*)malloc(sizeof(Resource));
    if (res == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    res->data = (int*)malloc(size * sizeof(int));
    if (res->data == NULL) {
        printf("Memory allocation failed.\n");
        free(res);
        return NULL;
    }
    res->size = size;
    return res;
}

void releaseResource(Resource *res) {
    if (res != NULL) {
        free(res->data);
        free(res);
    }
}

int main() {
    int size;
    printf("Enter resource size: ");
    scanf("%d", &size);
    Resource *res = createResource(size);
    if (res != NULL) {
        for (int i = 0; i < res->size; i++) {
            res->data[i] = i + 1;
        }
        for (int i = 0; i < res->size; i++) {
            printf("%d ", res->data[i]);
        }
        printf("\n");
        releaseResource(res);
    }
    return 0;
}