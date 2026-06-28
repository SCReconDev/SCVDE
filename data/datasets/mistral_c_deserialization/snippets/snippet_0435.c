#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheEntry;

void restore_cache(CacheEntry* entry) {
    printf("Restoring cache entry: %s = %s\n", entry->key, entry->value);
}

int main() {
    char* cache_blob = "{\"key\":\"config\",\"value\":\"production\"}";
    CacheEntry* entry = (CacheEntry*)malloc(sizeof(CacheEntry));
    memcpy(entry, cache_blob, sizeof(CacheEntry));
    restore_cache(entry);
    free(entry);
    return 0;
}