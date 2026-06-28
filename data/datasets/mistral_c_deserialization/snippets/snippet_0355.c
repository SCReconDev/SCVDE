#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void deserialize_cache_item(const char* data, CacheItem* item) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %49s", item->key, item->value);
    free(decoded_data);
}

void restore_cache(const char* cache_data) {
    CacheItem item;
    deserialize_cache_item(cache_data, &item);
    printf("Cache Item: %s = %s\n", item.key, item.value);
}

int main() {
    const char* cache_data = "user_token abc123";
    restore_cache(cache_data);
    return 0;
}