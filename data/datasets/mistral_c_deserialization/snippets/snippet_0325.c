#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void deserialize_cache_item(const char* data, CacheItem* item) {
    sscanf(data, "%49[^|]|%49[^|]", item->key, item->value);
}

int main() {
    char blob[100];
    CacheItem item;

    printf("Enter cache blob (key|value): ");
    fgets(blob, sizeof(blob), stdin);
    blob[strcspn(blob, "\n")] = '\0';

    deserialize_cache_item(blob, &item);

    printf("Key: %s\nValue: %s\n", item.key, item.value);

    return 0;
}