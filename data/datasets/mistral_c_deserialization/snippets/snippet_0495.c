#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void deserialize_cache_item(const char* data, CacheItem* item) {
    char* token = strtok((char*)data, ":");
    item->key = strdup(token);
    token = strtok(NULL, ":");
    item->value = strdup(token);
}

void restore_cache(const char* cache_data) {
    CacheItem item;
    deserialize_cache_item(cache_data, &item);
    printf("Cache Key: %s, Cache Value: %s\n", item.key, item.value);
    free(item.key);
    free(item.value);
}

int main() {
    const char* cache_data = "user_prefs:dark_mode=true";
    restore_cache(cache_data);
    return 0;
}