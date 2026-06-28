#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} Collection;

void create_collection(Collection *collection, size_t size) {
    collection->data = (int *)malloc(size * sizeof(int));
    if (collection->data == NULL) {
        printf("Memory allocation failed\n");
        collection->size = 0;
        return;
    }
    collection->size = size;
    for (size_t i = 0; i < size; i++) {
        collection->data[i] = i;
    }
}

void release_collection(Collection *collection) {
    if (collection->data != NULL) {
        free(collection->data);
        collection->data = NULL;
    }
    collection->size = 0;
}

int main() {
    Collection collection;
    size_t size;
    printf("Enter size: ");
    scanf("%zu", &size);
    create_collection(&collection, size);
    for (size_t i = 0; i < collection.size; i++) {
        printf("Collection element at index %zu: %d\n", i, collection.data[i]);
    }
    release_collection(&collection);
    return 0;
}