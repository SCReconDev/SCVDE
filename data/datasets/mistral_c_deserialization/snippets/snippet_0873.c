#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char cache_key[256];
    char cache_value[256];
    int ttl;
} CacheEntry;

int validate_cache_entry(CacheEntry *entry) {
    if (strlen(entry->cache_key) == 0 || strlen(entry->cache_value) == 0 || entry->ttl <= 0) {
        return 0;
    }
    return 1;
}

CacheEntry* deserialize_cache_entry(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *cache_key_obj, *cache_value_obj, *ttl_obj;
    CacheEntry *entry = malloc(sizeof(CacheEntry));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(entry);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "cache_key", &cache_key_obj);
    json_object_object_get_ex(parsed_json, "cache_value", &cache_value_obj);
    json_object_object_get_ex(parsed_json, "ttl", &ttl_obj);

    if (cache_key_obj == NULL || cache_value_obj == NULL || ttl_obj == NULL) {
        json_object_put(parsed_json);
        free(entry);
        return NULL;
    }

    strncpy(entry->cache_key, json_object_get_string(cache_key_obj), sizeof(entry->cache_key) - 1);
    strncpy(entry->cache_value, json_object_get_string(cache_value_obj), sizeof(entry->cache_value) - 1);
    entry->ttl = json_object_get_int(ttl_obj);

    json_object_put(parsed_json);

    if (!validate_cache_entry(entry)) {
        free(entry);
        return NULL;
    }

    return entry;
}

void process_cache_entry(CacheEntry *entry) {
    printf("Processing cache entry: %s, %s, %d\n", entry->cache_key, entry->cache_value, entry->ttl);
}

int main() {
    char input[MAX_INPUT_SIZE];
    CacheEntry *entry;

    printf("Enter cache entry data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    entry = deserialize_cache_entry(input);
    if (entry == NULL) {
        printf("Invalid cache entry data\n");
        return 1;
    }

    process_cache_entry(entry);

    free(entry);
    return 0;
}