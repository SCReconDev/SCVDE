#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void deserialize_cache_item(CacheItem* item, const char* data) {
    char* token = strtok((char*)data, "|");
    item->key = strdup(token);
    token = strtok(NULL, "|");
    item->value = strdup(token);
}

int main() {
    FILE* file = fopen("cache_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    CacheItem item;
    deserialize_cache_item(&item, buffer);

    printf("Key: %s, Value: %s\n", item.key, item.value);

    free(item.key);
    free(item.value);
    fclose(file);
    return 0;
}