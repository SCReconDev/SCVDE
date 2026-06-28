#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[100];
} CacheItem;

void restore_cache(char* blob) {
    CacheItem* item = (CacheItem*)malloc(sizeof(CacheItem));
    memcpy(item, blob, sizeof(CacheItem));
    printf("Cache restored: %s = %s\n", item->key, item->value);
    free(item);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <stored_blob>\n", argv[0]);
        return 1;
    }

    char* blob = argv[1];
    restore_cache(blob);

    return 0;
}