#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char cache_key[50];
    char cache_value[100];
    int ttl;
} CacheItem;

bool validate_cache_item(CacheItem* item) {
    if (strlen(item->cache_key) == 0 || strlen(item->cache_value) == 0) {
        return false;
    }
    if (item->ttl < 0) {
        return false;
    }
    return true;
}

void restore_cache(CacheItem* item) {
    if (validate_cache_item(item)) {
        printf("Cache restored: %s, %s, %d\n", item->cache_key, item->cache_value, item->ttl);
    } else {
        printf("Invalid cache data\n");
    }
}

int main() {
    CacheItem item1 = {"key1", "value1", 3600};
    CacheItem item2 = {"", "value2", -100};

    restore_cache(&item1);
    restore_cache(&item2);

    return 0;
}