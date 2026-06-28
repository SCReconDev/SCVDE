#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void deserialize_cache_item(char* data, CacheItem* item) {
    char* token = strtok(data, "|");
    item->key = strdup(token);
    token = strtok(NULL, "|");
    item->value = strdup(token);
}

void restore_cache(char* blob) {
    CacheItem item;
    deserialize_cache_item(blob, &item);
    printf("Key: %s, Value: %s\n", item.key, item.value);
    free(item.key);
    free(item.value);
}

int main() {
    char* blob = "user_data|John Doe";
    restore_cache(blob);
    return 0;
}