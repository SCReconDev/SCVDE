#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char data[100];
} CacheItem;

void deserialize_cache_item(CacheItem *item, const char *blob) {
    sscanf(blob, "%d %99s", &item->id, item->data);
}

void restore_cache(const char *blob) {
    CacheItem item;
    deserialize_cache_item(&item, blob);
    printf("Restored cache item: %d, %s\n", item.id, item.data);
}

int main() {
    char blob[200];
    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);
    restore_cache(blob);
    return 0;
}