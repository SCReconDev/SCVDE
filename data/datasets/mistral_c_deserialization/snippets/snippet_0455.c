#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[100];
} CacheItem;

void deserialize_cache_item(char* data, CacheItem* item) {
    char* token = strtok(data, ":");
    strcpy(item->key, token);
    token = strtok(NULL, ":");
    strcpy(item->value, token);
}

void restore_cache(char* blob) {
    CacheItem item;
    deserialize_cache_item(blob, &item);
    printf("Restored cache item: %s, %s\n", item.key, item.value);
}

int main() {
    char blob[] = "user:Alice";
    restore_cache(blob);
    return 0;
}