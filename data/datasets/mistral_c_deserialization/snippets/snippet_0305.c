#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheEntry;

void deserialize_cache_entry(char* data, CacheEntry* entry) {
    char* token = strtok(data, "|");
    entry->key = strdup(token);
    token = strtok(NULL, "|");
    entry->value = strdup(token);
}

void restore_cache(char* blob) {
    CacheEntry entry;
    deserialize_cache_entry(blob, &entry);
    printf("Key: %s, Value: %s\n", entry.key, entry.value);
    free(entry.key);
    free(entry.value);
}

int main() {
    char* blob = "user_data|{\"name\":\"John Doe\",\"age\":30}";
    restore_cache(blob);
    return 0;
}