#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char key[50];
    char value[100];
} CacheItem;

int deserialize_cache_item(const char* json_str, CacheItem* item) {
    struct json_object *parsed_json;
    struct json_object *key_obj, *value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "key", &key_obj)) {
        fprintf(stderr, "Error getting key\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "value", &value_obj)) {
        fprintf(stderr, "Error getting value\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(item->key, json_object_get_string(key_obj), sizeof(item->key) - 1);
    strncpy(item->value, json_object_get_string(value_obj), sizeof(item->value) - 1);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    CacheItem item;

    printf("Enter cache item JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_cache_item(buffer, &item) == 0) {
        printf("Deserialized Cache Item: Key=%s, Value=%s\n", item.key, item.value);
    } else {
        fprintf(stderr, "Failed to deserialize cache item\n");
    }

    return 0;
}