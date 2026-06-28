#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void restore_cache(const char* blob) {
    CacheItem* item = (CacheItem*)malloc(sizeof(CacheItem));
    memcpy(item, blob, sizeof(CacheItem));
    printf("Cache Item: %s = %s\n", item->key, item->value);
    free(item);
}

int main() {
    char blob[100];
    printf("Enter blob: ");
    fgets(blob, sizeof(blob), stdin);
    restore_cache(blob);
    return 0;
}