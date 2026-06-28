#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void deserialize_cache_item(const char* json_str, CacheItem* cache_item) {
    struct json_object* parsed_json;
    struct json_object* key;
    struct json_object* value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "key", &key);
    json_object_object_get_ex(parsed_json, "value", &value);

    if (key != NULL && json_object_is_type(key, json_type_string)) {
        cache_item->key = strdup(json_object_get_string(key));
    }

    if (value != NULL && json_object_is_type(value, json_type_string)) {
        cache_item->value = strdup(json_object_get_string(value));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode\"}";
    CacheItem cache_item;

    deserialize_cache_item(json_str, &cache_item);

    printf("Key: %s\n", cache_item.key);
    printf("Value: %s\n", cache_item.value);

    free(cache_item.key);
    free(cache_item.value);
    return 0;
}