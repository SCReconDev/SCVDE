#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheEntry;

void restore_cache(const char* blob, CacheEntry* entry) {
    char* data = strdup(blob);
    char* token = strtok(data, ":");
    entry->key = strdup(token);
    token = strtok(NULL, ":");
    entry->value = strdup(token);
    free(data);
}

int main() {
    char* cache_blob = "user_token:abc123xyz";
    CacheEntry entry;
    restore_cache(cache_blob, &entry);
    printf("Cache Key: %s, Cache Value: %s\n", entry.key, entry.value);
    free(entry.key);
    free(entry.value);
    return 0;
}