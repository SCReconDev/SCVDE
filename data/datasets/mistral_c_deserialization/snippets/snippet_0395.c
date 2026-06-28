#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache(CacheItem* item) {
    printf("Key: %s\n", item->key);
    printf("Value: %s\n", item->value);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <stored_blob>\n", argv[0]);
        return 1;
    }

    char* stored_blob = argv[1];
    CacheItem* item = (CacheItem*)stored_blob;
    restore_cache(item);

    return 0;
}