#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void process_cache_item(CacheItem* item) {
    printf("Cache Item - Key: %s, Value: %s\n", item->key, item->value);
}

int main() {
    const char* cache_blob = "{\"key\":\"user_data\",\"value\":\"{\\\"name\\\":\\\"Jane Doe\\\",\\\"age\\\":25}\"}";
    struct json_object* parsed_json;
    struct json_object* key_obj;
    struct json_object* value_obj;
    CacheItem item;

    parsed_json = json_tokener_parse(cache_blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "key", &key_obj) ||
        !json_object_object_get_ex(parsed_json, "value", &value_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    item.key = strdup(json_object_get_string(key_obj));
    item.value = strdup(json_object_get_string(value_obj));

    process_cache_item(&item);

    free(item.key);
    free(item.value);
    json_object_put(parsed_json);

    return 0;
}