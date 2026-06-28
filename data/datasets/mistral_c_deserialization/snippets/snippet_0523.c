#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char cache_key[MAX_BUFFER_SIZE];
    char cache_value[MAX_BUFFER_SIZE];
} CacheEntry;

void restore_cache_entry(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *cache_key_obj, *cache_value_obj;
    CacheEntry entry;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "cache_key", &cache_key_obj) ||
        !json_object_object_get_ex(parsed_json, "cache_value", &cache_value_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(entry.cache_key, json_object_get_string(cache_key_obj), MAX_BUFFER_SIZE - 1);
    strncpy(entry.cache_value, json_object_get_string(cache_value_obj), MAX_BUFFER_SIZE - 1);

    printf("Cache Key: %s, Cache Value: %s\n", entry.cache_key, entry.cache_value);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"cache_key\":\"key1\",\"cache_value\":\"value1\"}";
    restore_cache_entry(json_data);
    return 0;
}