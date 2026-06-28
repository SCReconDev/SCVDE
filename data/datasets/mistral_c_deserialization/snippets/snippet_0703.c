#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char key[50];
    char value[255];
} CacheItem;

bool validate_cache_item(CacheItem* item) {
    if (strlen(item->key) == 0 || strlen(item->key) >= 50) {
        return false;
    }
    if (strlen(item->value) >= 255) {
        return false;
    }
    return true;
}

void process_cache_item(CacheItem* item) {
    if (validate_cache_item(item)) {
        printf("Cache Item - Key: %s, Value: %s\n", item->key, item->value);
    } else {
        printf("Invalid cache item data\n");
    }
}

int main() {
    CacheItem item1 = {"user_prefs", "{\"theme\": \"dark\", \"language\": \"en\"}"};
    CacheItem item2 = {"", "{\"invalid\": \"data\"}"};

    process_cache_item(&item1);
    process_cache_item(&item2);

    return 0;
}