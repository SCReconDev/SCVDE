#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char cache_key[50];
    char cache_value[100];
    int ttl;
} CacheEntry;

int validate_cache_entry_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *cache_key_obj, *cache_value_obj, *ttl_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "cache_key", &cache_key_obj) ||
        !json_object_object_get_ex(parsed_json, "cache_value", &cache_value_obj) ||
        !json_object_object_get_ex(parsed_json, "ttl", &ttl_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(cache_key_obj) != json_type_string ||
        json_object_get_type(cache_value_obj) != json_type_string ||
        json_object_get_type(ttl_obj) != json_type_int) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

CacheEntry* deserialize_cache_entry(const char *json_str) {
    CacheEntry *entry = malloc(sizeof(CacheEntry));
    if (!entry) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *cache_key_obj, *cache_value_obj, *ttl_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(entry);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "cache_key", &cache_key_obj);
    json_object_object_get_ex(parsed_json, "cache_value", &cache_value_obj);
    json_object_object_get_ex(parsed_json, "ttl", &ttl_obj);

    strncpy(entry->cache_key, json_object_get_string(cache_key_obj), sizeof(entry->cache_key) - 1);
    strncpy(entry->cache_value, json_object_get_string(cache_value_obj), sizeof(entry->cache_value) - 1);
    entry->ttl = json_object_get_int(ttl_obj);

    json_object_put(parsed_json);
    return entry;
}

void process_cache_entry_data(const char *json_str) {
    if (!validate_cache_entry_json(json_str)) {
        printf("Invalid cache entry data format\n");
        return;
    }

    CacheEntry *entry = deserialize_cache_entry(json_str);
    if (!entry) {
        printf("Failed to deserialize cache entry data\n");
        return;
    }

    printf("Cache Key: %s, Cache Value: %s, TTL: %d\n", entry->cache_key, entry->cache_value, entry->ttl);
    free(entry);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter cache entry data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_cache_entry_data(buffer);

    return 0;
}