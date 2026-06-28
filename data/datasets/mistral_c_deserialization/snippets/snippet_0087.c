#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void restore_cache(CacheItem *item, const char *blob) {
    char *token = strtok((char *)blob, ",");
    strcpy(item->key, token);
    token = strtok(NULL, ",");
    strcpy(item->value, token);
}

int main() {
    char blob[100];
    CacheItem item;

    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);

    restore_cache(&item, blob);

    printf("Cache Item: Key=%s, Value=%s\n", item.key, item.value);

    return 0;
}