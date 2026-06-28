#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void restore_cache(const char* data, CacheItem* item) {
    sscanf(data, "%49s %49s", item->key, item->value);
}

int main() {
    char blob[100];
    CacheItem item;

    printf("Enter cache blob (key value): ");
    fgets(blob, sizeof(blob), stdin);

    restore_cache(blob, &item);

    printf("Restored Cache Item: Key=%s, Value=%s\n", item.key, item.value);

    return 0;
}