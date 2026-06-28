#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache(CacheItem* item) {
    printf("Cache Item: Key=%s, Value=%s\n", item->key, item->value);
}

int main() {
    const char* blob = "{\"key\":\"item1\",\"value\":\"data1\"}";
    struct json_object* json_obj = json_tokener_parse(blob);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    CacheItem item;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "key") == 0) {
            item.key = strdup(json_object_get_string(val));
        } else if (strcmp(key, "value") == 0) {
            item.value = strdup(json_object_get_string(val));
        }
    }

    restore_cache(&item);
    free(item.key);
    free(item.value);
    json_object_put(json_obj);

    return 0;
}