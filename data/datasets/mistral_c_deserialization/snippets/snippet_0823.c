#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *key;
    char *value;
} CacheItem;

void parse_cache_item(json_object *jobj, CacheItem *item) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "key") == 0) {
            item->key = strdup(json_object_get_string(val));
        } else if (strcmp(key, "value") == 0) {
            item->value = strdup(json_object_get_string(val));
        }
    }
}

int main() {
    const char *blob = "{\"key\":\"item1\",\"value\":\"data123\"}";
    json_object *jobj = json_tokener_parse(blob);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    CacheItem item;
    parse_cache_item(jobj, &item);

    printf("Key: %s\n", item.key);
    printf("Value: %s\n", item.value);

    free(item.key);
    free(item.value);
    json_object_put(jobj);

    return 0;
}