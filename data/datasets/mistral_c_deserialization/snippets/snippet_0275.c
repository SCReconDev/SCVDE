#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache(CacheItem* item, const char* blob) {
    char* token = strtok((char*)blob, ":");
    item->key = strdup(token);
    token = strtok(NULL, ":");
    item->value = strdup(token);
}

int main() {
    char blob[100];
    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);
    blob[strcspn(blob, "\n")] = 0;

    CacheItem item;
    restore_cache(&item, blob);

    printf("Key: %s, Value: %s\n", item.key, item.value);
    free(item.key);
    free(item.value);
    return 0;
}