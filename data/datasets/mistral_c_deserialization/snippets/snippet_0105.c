#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* data;
} CacheItem;

void restore_cache(CacheItem* item, const char* blob) {
    char* token = strdup(blob);
    char* part = strtok(token, "|");
    item->id = atoi(part);
    part = strtok(NULL, "|");
    item->data = strdup(part);
    free(token);
}

int main() {
    char* blob = "123|Some cached data";
    CacheItem item;
    restore_cache(&item, blob);
    printf("ID: %d, Data: %s\n", item.id, item.data);
    return 0;
}