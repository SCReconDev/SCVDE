#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void parse_cache_blob(const char* blob) {
    struct json_object* parsed_json;
    struct json_object* key;
    struct json_object* value;

    parsed_json = json_tokener_parse(blob);

    if (json_object_object_get_ex(parsed_json, "key", &key)) {
        CacheItem* item = (CacheItem*)malloc(sizeof(CacheItem));
        item->key = strdup(json_object_get_string(key));

        if (json_object_object_get_ex(parsed_json, "value", &value)) {
            item->value = strdup(json_object_get_string(value));
        } else {
            item->value = strdup("");
        }

        printf("Key: %s, Value: %s\n", item->key, item->value);
        free(item->key);
        free(item->value);
        free(item);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* blob = "{\"key\":\"cache_key\",\"value\":\"cache_value\"}";
    parse_cache_blob(blob);
    return 0;
}