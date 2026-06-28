#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void restore_cache(const char* blob) {
    CacheItem* item = (CacheItem*)malloc(sizeof(CacheItem));
    memcpy(item, blob, sizeof(CacheItem));
    printf("Key: %s, Value: %s\n", item->key, item->value);
    free(item);
}

int main() {
    char blob[sizeof(CacheItem)];
    memset(blob, 0, sizeof(blob));
    strcpy(blob, "config");
    strcpy(blob + 50, "settings");

    restore_cache(blob);
    return 0;
}