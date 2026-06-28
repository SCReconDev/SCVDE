#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void deserialize_cache_item(CacheItem *item, const char *data) {
    char *token = strtok((char *)data, "|");
    strcpy(item->key, token);
    token = strtok(NULL, "|");
    strcpy(item->value, token);
}

void restore_cache(const char *blob) {
    CacheItem item;
    deserialize_cache_item(&item, blob);
    printf("Cache restored: Key=%s, Value=%s\n", item.key, item.value);
}

int main() {
    const char *blob = "user|admin";
    restore_cache(blob);
    return 0;
}