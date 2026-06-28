#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache(const char* blob) {
    CacheItem* item = (CacheItem*)blob;
    printf("Cache Item: %s = %s\n", item->key, item->value);
}

int main() {
    const char* cache_blob = "{\"key\":\"theme\",\"value\":\"dark\"}";
    restore_cache(cache_blob);
    return 0;
}