#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache(const char* blob) {
    CacheItem item;
    char* decoded = strdup(blob);
    char* token = strtok(decoded, ":");
    item.key = strdup(token);
    token = strtok(NULL, ":");
    item.value = strdup(token);
    printf("Cache restored: %s = %s\n", item.key, item.value);
    free(item.key);
    free(item.value);
    free(decoded);
}

int main() {
    const char* blob = "last_login:2023-10-01";
    restore_cache(blob);
    return 0;
}