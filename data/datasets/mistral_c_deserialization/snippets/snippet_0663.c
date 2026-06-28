#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char key[MAX_BUFFER_SIZE];
    char value[MAX_BUFFER_SIZE];
} CacheEntry;

void restore_cache_entry(const char *json_str, CacheEntry *entry) {
    struct json_object *parsed_json;
    struct json_object *key_obj;
    struct json_object *value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "key", &key_obj);
    if (key_obj != NULL) {
        strncpy(entry->key, json_object_get_string(key_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "value", &value_obj);
    if (value_obj != NULL) {
        strncpy(entry->value, json_object_get_string(value_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode\"}";
    CacheEntry entry;

    restore_cache_entry(json_str, &entry);

    printf("Key: %s\n", entry.key);
    printf("Value: %s\n", entry.value);

    return 0;
}