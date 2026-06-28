#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BLOB_SIZE 1024

typedef struct {
    char cache_key[256];
    int cache_value;
    char cache_data[256];
} CacheEntry;

void deserialize_cache_entry(CacheEntry *entry, const char *blob) {
    struct json_object *parsed_json;
    struct json_object *cache_key_obj, *cache_value_obj, *cache_data_obj;

    parsed_json = json_tokener_parse(blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON blob\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "cache_key", &cache_key_obj);
    json_object_object_get_ex(parsed_json, "cache_value", &cache_value_obj);
    json_object_object_get_ex(parsed_json, "cache_data", &cache_data_obj);

    if (cache_key_obj != NULL && json_object_is_type(cache_key_obj, json_type_string)) {
        strncpy(entry->cache_key, json_object_get_string(cache_key_obj), sizeof(entry->cache_key) - 1);
    }

    if (cache_value_obj != NULL && json_object_is_type(cache_value_obj, json_type_int)) {
        entry->cache_value = json_object_get_int(cache_value_obj);
    }

    if (cache_data_obj != NULL && json_object_is_type(cache_data_obj, json_type_string)) {
        strncpy(entry->cache_data, json_object_get_string(cache_data_obj), sizeof(entry->cache_data) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    CacheEntry entry;
    char blob[MAX_BLOB_SIZE];

    printf("Enter cache blob: ");
    fgets(blob, sizeof(blob), stdin);

    deserialize_cache_entry(&entry, blob);

    printf("Deserialized Cache Entry:\n");
    printf("Cache Key: %s\n", entry.cache_key);
    printf("Cache Value: %d\n", entry.cache_value);
    printf("Cache Data: %s\n", entry.cache_data);

    return 0;
}