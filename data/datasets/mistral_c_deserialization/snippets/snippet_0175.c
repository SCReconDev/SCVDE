#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* data;
} CacheItem;

void restore_cache(char* blob) {
    CacheItem* item = (CacheItem*)malloc(sizeof(CacheItem));
    memcpy(item, blob, sizeof(CacheItem));
    printf("Cache Item ID: %d\n", item->id);
    free(item);
}

int main() {
    char blob[1024];
    fgets(blob, sizeof(blob), stdin);
    restore_cache(blob);
    return 0;
}