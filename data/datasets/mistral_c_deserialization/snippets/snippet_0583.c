#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void deserialize_cache_item(const char* json_str, CacheItem* item) {
    struct json_object* parsed_json;
    struct json_object* key_obj;
    struct json_object* value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "key", &key_obj);
    json_object_object_get_ex(parsed_json, "value", &value_obj);

    if (key_obj != NULL && json_object_is_type(key_obj, json_type_string)) {
        item->key = strdup(json_object_get_string(key_obj));
    }

    if (value_obj != NULL && json_object_is_type(value_obj, json_type_string)) {
        item->value = strdup(json_object_get_string(value_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode\"}";
    CacheItem item;

    deserialize_cache_item(json_str, &item);

    printf("Key: %s\n", item.key);
    printf("Value: %s\n", item.value);

    free(item.key);
    free(item.value);
    return 0;
}