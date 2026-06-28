#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} CacheEntry;

void restore_cache(const char* blob, CacheEntry* entry) {
    char* token = strtok((char*)blob, ",");
    entry->key = strdup(token);
    token = strtok(NULL, ",");
    entry->value = atoi(token);
}

int main() {
    char* blob = "temperature,25";
    CacheEntry entry;
    restore_cache(blob, &entry);
    printf("Key: %s, Value: %d\n", entry.key, entry.value);
    free(entry.key);
    return 0;
}