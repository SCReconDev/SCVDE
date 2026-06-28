#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[256];
    char value[256];
} CacheItem;

void deserialize_cache_item(CacheItem *item, const char *data) {
    sscanf(data, "%255[^;];%255[^;]", item->key, item->value);
}

void restore_cache(const char *blob) {
    CacheItem item;
    deserialize_cache_item(&item, blob);
    printf("Cache Item: %s = %s\n", item.key, item.value);
}

int main() {
    char blob[512];
    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);
    restore_cache(blob);
    return 0;
}