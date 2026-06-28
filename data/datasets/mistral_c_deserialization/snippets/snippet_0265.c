#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[50];
    char value[50];
} CacheItem;

void restore_cache(CacheItem *item, const char *blob) {
    char *token = strtok((char *)blob, "|");
    if (token != NULL) {
        strncpy(item->key, token, sizeof(item->key) - 1);
        token = strtok(NULL, "|");
        if (token != NULL) {
            strncpy(item->value, token, sizeof(item->value) - 1);
        }
    }
}

int main() {
    char blob[100];
    CacheItem item;

    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);

    restore_cache(&item, blob);

    printf("Restored Cache Item: Key=%s, Value=%s\n", item.key, item.value);

    return 0;
}