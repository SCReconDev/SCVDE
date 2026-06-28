#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void process_cache_item(CacheItem* item) {
    printf("Key: %s\n", item->key);
    printf("Value: %s\n", item->value);
}

void deserialize_cache_item(const char* blob, CacheItem* item) {
    char* data = strdup(blob);
    char* token = strtok(data, "|");
    item->key = strdup(token);
    token = strtok(NULL, "|");
    item->value = strdup(token);
    free(data);
}

void restore_cache(const char* blob) {
    CacheItem item;
    deserialize_cache_item(blob, &item);
    process_cache_item(&item);
}

int main() {
    const char* blob = "user_prefs|{\"theme\":\"dark\",\"font\":\"12\"}";
    restore_cache(blob);
    return 0;
}