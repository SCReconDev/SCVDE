#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache_item(const char* json_str, CacheItem* item) {
    struct json_object* parsed_json;
    struct json_object* key;
    struct json_object* value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "key", &key)) {
        fprintf(stderr, "Error: 'key' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "value", &value)) {
        fprintf(stderr, "Error: 'value' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    item->key = strdup(json_object_get_string(key));
    item->value = strdup(json_object_get_string(value));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"key\":\"item1\",\"value\":\"data1\"}";
    CacheItem item;

    restore_cache_item(json_str, &item);

    printf("Key: %s\n", item.key);
    printf("Value: %s\n", item.value);

    free(item.key);
    free(item.value);
    return 0;
}