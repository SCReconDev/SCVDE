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
    struct json_object* key_obj;
    struct json_object* value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "key", &key_obj)) {
        fprintf(stderr, "Error getting key from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "value", &value_obj)) {
        fprintf(stderr, "Error getting value from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    cache_item->key = strdup(json_object_get_string(key_obj));
    cache_item->value = strdup(json_object_get_string(value_obj));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode=true\"}";
    CacheItem cache_item;

    deserialize_cache_item(json_str, &cache_item);

    printf("Key: %s\n", cache_item.key);
    printf("Value: %s\n", cache_item.value);

    free(cache_item.key);
    free(cache_item.value);

    return 0;
}