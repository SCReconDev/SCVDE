#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} CacheEntry;

void restore_cache(const char* blob) {
    CacheEntry* entry = (CacheEntry*)malloc(sizeof(CacheEntry));
    memcpy(entry, blob, sizeof(CacheEntry));

    printf("Cache Entry: %s, Value: %d\n", entry->key, entry->value);
    free(entry);
}

int main() {
    char* cache_blob = "temperature\072";
    restore_cache(cache_blob);
    return 0;
}