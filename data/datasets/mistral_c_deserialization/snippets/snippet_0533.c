#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheEntry;

void deserialize_cache_entry(const char* json_str, CacheEntry* entry) {
    struct json_object* parsed_json;
    struct json_object* key;
    struct json_object* value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "key", &key);
    json_object_object_get_ex(parsed_json, "value", &value);

    if (key != NULL && value != NULL) {
        entry->key = strdup(json_object_get_string(key));
        entry->value = strdup(json_object_get_string(value));
    } else {
        fprintf(stderr, "Invalid JSON format\n");
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"key\":\"cache_key\",\"value\":\"cache_value\"}";
    CacheEntry entry;

    deserialize_cache_entry(json_str, &entry);

    printf("Key: %s\n", entry.key);
    printf("Value: %s\n", entry.value);

    free(entry.key);
    free(entry.value);

    return 0;
}