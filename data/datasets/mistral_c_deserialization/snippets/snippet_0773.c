#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *key;
    char *value;
} CacheItem;

void parse_cache_item(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *key;
    struct json_object *value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "key", &key)) {
        fprintf(stderr, "Key not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "value", &value)) {
        fprintf(stderr, "Value not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    CacheItem item;
    item.key = strdup(json_object_get_string(key));
    item.value = strdup(json_object_get_string(value));

    printf("Key: %s, Value: %s\n", item.key, item.value);

    free(item.key);
    free(item.value);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode\"}";
    parse_cache_item(json_str);
    return 0;
}