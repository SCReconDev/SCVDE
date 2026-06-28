#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheEntry;

void restore_cache(const char* blob, CacheEntry* entry) {
    char* data = strdup(blob);
    char* token = strtok(data, ":");
    strcpy(entry->key, token);
    token = strtok(NULL, ":");
    strcpy(entry->value, token);
    free(data);
}

int main() {
    char* blob = "user_token:abc123";
    CacheEntry entry;
    restore_cache(blob, &entry);
    printf("Key: %s, Value: %s\n", entry.key, entry.value);
    return 0;
}