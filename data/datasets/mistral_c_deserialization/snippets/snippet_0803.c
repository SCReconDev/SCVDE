#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *key;
    char *value;
} CacheEntry;

void deserialize_cache_entry(const char *json_str, CacheEntry *entry) {
    struct json_object *parsed_json;
    struct json_object *key_obj, *value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "key", &key_obj);
    json_object_object_get_ex(parsed_json, "value", &value_obj);

    if (key_obj != NULL && json_object_get_type(key_obj) == json_type_string) {
        entry->key = strdup(json_object_get_string(key_obj));
    }

    if (value_obj != NULL && json_object_get_type(value_obj) == json_type_string) {
        entry->value = strdup(json_object_get_string(value_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode\"}";
    CacheEntry entry;

    deserialize_cache_entry(json_str, &entry);

    printf("Key: %s\n", entry.key);
    printf("Value: %s\n", entry.value);

    free(entry.key);
    free(entry.value);
    return 0;
}