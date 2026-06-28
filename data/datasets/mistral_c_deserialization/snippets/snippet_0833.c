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

    if (key != NULL && json_object_get_type(key) == json_type_string) {
        entry->key = strdup(json_object_get_string(key));
    }

    if (value != NULL && json_object_get_type(value) == json_type_string) {
        entry->value = strdup(json_object_get_string(value));
    }

    json_object_put(parsed_json);
}

void restore_cache(const char* blob) {
    CacheEntry entry = {NULL, NULL};
    deserialize_cache_entry(blob, &entry);

    if (entry.key != NULL) {
        printf("Key: %s\n", entry.key);
        free(entry.key);
    }

    if (entry.value != NULL) {
        printf("Value: %s\n", entry.value);
        free(entry.value);
    }
}

int main() {
    const char* blob = "{\"key\":\"example\",\"value\":\"data\"}";
    restore_cache(blob);
    return 0;
}