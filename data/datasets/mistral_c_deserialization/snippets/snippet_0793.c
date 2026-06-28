#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *key;
    char *value;
} CacheItem;

void print_cache_item(CacheItem *item) {
    printf("Key: %s\n", item->key);
    printf("Value: %s\n", item->value);
}

int main() {
    const char *blob = "{\"key\":\"user_prefs\",\"value\":\"dark_mode=true\"}";
    struct json_object *parsed_json;
    struct json_object *key;
    struct json_object *value;
    CacheItem item;

    parsed_json = json_tokener_parse(blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "key", &key);
    json_object_object_get_ex(parsed_json, "value", &value);

    if (key == NULL || value == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    item.key = strdup(json_object_get_string(key));
    item.value = strdup(json_object_get_string(value));

    print_cache_item(&item);

    free(item.key);
    free(item.value);
    json_object_put(parsed_json);

    return 0;
}