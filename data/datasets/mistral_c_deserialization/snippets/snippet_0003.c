#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void deserialize_cache_item(CacheItem *item, const char *blob) {
    sscanf(blob, "%49s %49s", item->key, item->value);
}

void restore_cache(const char *blob) {
    CacheItem item;
    deserialize_cache_item(&item, blob);
    printf("Cache Item: %s = %s\n", item.key, item.value);
}

int main() {
    char blob[100];
    printf("Enter blob: ");
    fgets(blob, sizeof(blob), stdin);
    restore_cache(blob);
    return 0;
}