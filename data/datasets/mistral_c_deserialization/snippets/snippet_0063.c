#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void deserialize_cache_item(const char* blob, CacheItem* item) {
    char* token = strtok((char*)blob, ":");
    item->key = strdup(token);
    token = strtok(NULL, ":");
    item->value = strdup(token);
}

void restore_cache(const char* blob) {
    CacheItem item;
    deserialize_cache_item(blob, &item);
    printf("Cache Item - Key: %s, Value: %s\n", item.key, item.value);
    free(item.key);
    free(item.value);
}

int main() {
    const char* blob = "user_prefs:dark_mode";
    restore_cache(blob);
    return 0;
}