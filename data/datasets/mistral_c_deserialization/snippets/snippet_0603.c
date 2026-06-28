#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void process_cache_item(CacheItem* item) {
    printf("Key: %s\n", item->key);
    printf("Value: %s\n", item->value);
}

CacheItem* deserialize_cache_item(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* key_obj;
    struct json_object* value_obj;
    CacheItem* item = malloc(sizeof(CacheItem));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(item);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "key", &key_obj);
    json_object_object_get_ex(parsed_json, "value", &value_obj);

    if (key_obj == NULL || value_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(item);
        return NULL;
    }

    item->key = strdup(json_object_get_string(key_obj));
    item->value = strdup(json_object_get_string(value_obj));

    json_object_put(parsed_json);
    return item;
}

int main() {
    const char* json_str = "{\"key\":\"cache_key\",\"value\":\"cache_value\"}";
    CacheItem* item = deserialize_cache_item(json_str);

    if (item != NULL) {
        process_cache_item(item);
        free(item->key);
        free(item->value);
        free(item);
    }

    return 0;
}