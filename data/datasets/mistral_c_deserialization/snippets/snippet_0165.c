#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* data;
} CacheItem;

void restore_cache(CacheItem* item, const char* blob) {
    char* token = strtok((char*)blob, "|");
    item->id = atoi(token);
    token = strtok(NULL, "|");
    item->data = strdup(token);
}

void process_cache(const char* blob) {
    CacheItem item;
    restore_cache(&item, blob);
    printf("ID: %d, Data: %s\n", item.id, item.data);
    free(item.data);
}

int main() {
    const char* blob = "123|sample data";
    process_cache(blob);
    return 0;
}