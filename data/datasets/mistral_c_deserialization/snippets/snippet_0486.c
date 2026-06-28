#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache(char* blob) {
    CacheItem* item = (CacheItem*)malloc(sizeof(CacheItem));
    memcpy(item, blob, sizeof(CacheItem));
    printf("Cache Item: %s = %s\n", item->key, item->value);
    free(item);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <blob>\n", argv[0]);
        return 1;
    }
    restore_cache(argv[1]);
    return 0;
}