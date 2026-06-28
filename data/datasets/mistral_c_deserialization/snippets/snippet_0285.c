#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheEntry;

void restore_cache(CacheEntry *entry, const char *blob) {
    sscanf(blob, "%49s %49s", entry->key, entry->value);
}

void load_cache(const char *blob) {
    CacheEntry entry;
    restore_cache(&entry, blob);
    printf("Cache Entry: %s = %s\n", entry.key, entry.value);
}

int main() {
    char blob[100];
    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);
    load_cache(blob);
    return 0;
}