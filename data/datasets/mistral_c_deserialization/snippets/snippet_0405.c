#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* data;
} CacheItem;

void restore_cache(const char* blob, CacheItem* item) {
    char* token = strtok((char*)blob, "|");
    item->id = atoi(token);
    token = strtok(NULL, "|");
    item->data = strdup(token);
}

int main() {
    char* cache_blob = "123|This is some cached data";
    CacheItem item;
    restore_cache(cache_blob, &item);
    printf("ID: %d, Data: %s\n", item.id, item.data);
    free(item.data);
    return 0;
}