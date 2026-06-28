#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char cache_key[50];
    char cache_data[200];
} CacheEntry;

void deserialize_cache_entry(CacheEntry *entry, const char *data) {
    memcpy(entry, data, sizeof(CacheEntry));
}

void restore_cache(const char *blob) {
    CacheEntry entry;
    deserialize_cache_entry(&entry, blob);
    printf("Restored cache entry: %s\n", entry.cache_key);
}

int main() {
    char blob[250];
    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);
    blob[strcspn(blob, "\n")] = '\0';

    restore_cache(blob);
    return 0;
}