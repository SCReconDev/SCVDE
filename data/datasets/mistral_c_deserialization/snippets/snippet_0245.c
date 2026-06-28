#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheEntry;

CacheEntry* restore_cache(const char* blob) {
    CacheEntry* entry = malloc(sizeof(CacheEntry));
    char* token = strtok((char*)blob, ",");
    entry->key = strdup(token);
    token = strtok(NULL, ",");
    entry->value = strdup(token);
    return entry;
}

void use_cache(const char* blob) {
    CacheEntry* entry = restore_cache(blob);
    printf("Cache Entry: %s = %s\n", entry->key, entry->value);
    free(entry->key);
    free(entry->value);
    free(entry);
}

int main() {
    char* blob = "user,admin";
    use_cache(blob);
    return 0;
}