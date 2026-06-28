#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} CacheEntry;

void deserialize_cache_entry(CacheEntry* entry, const char* data) {
    char* token = strtok((char*)data, "|");
    entry->key = strdup(token);
    token = strtok(NULL, "|");
    entry->value = atoi(token);
}

void restore_cache(const char* blob) {
    CacheEntry entry;
    deserialize_cache_entry(&entry, blob);
    printf("Cache Entry - Key: %s, Value: %d\n", entry.key, entry.value);
    free(entry.key);
}

int main() {
    const char* blob = "temperature|25";
    restore_cache(blob);
    return 0;
}