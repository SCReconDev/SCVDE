#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void restore_cache(const char* blob, CacheItem* item) {
    sscanf(blob, "%49s %49s", item->key, item->value);
}

void load_cache(const char* blob) {
    CacheItem item;
    restore_cache(blob, &item);
    printf("Cache Item: %s = %s\n", item.key, item.value);
}

int main() {
    char blob[100];
    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);
    load_cache(blob);
    return 0;
}