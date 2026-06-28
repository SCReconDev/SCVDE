#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheEntry;

void restore_cache(CacheEntry* entry, const char* data) {
    char* token = strtok((char*)data, "|");
    entry->key = strdup(token);
    token = strtok(NULL, "|");
    entry->value = strdup(token);
}

int main() {
    char* cache_data = "user_token|abc123xyz";
    CacheEntry entry;
    restore_cache(&entry, cache_data);
    printf("Key: %s, Value: %s\n", entry.key, entry.value);
    free(entry.key);
    free(entry.value);
    return 0;
}