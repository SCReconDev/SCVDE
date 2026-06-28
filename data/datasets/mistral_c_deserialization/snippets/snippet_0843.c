#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BLOB_SIZE 4096

typedef struct {
    char key[50];
    char value[100];
} CacheItem;

void restore_cache(const char *blob_data) {
    struct json_object *parsed_json;
    struct json_object *items_array;
    size_t i, array_length;
    CacheItem item;

    parsed_json = json_tokener_parse(blob_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing cache blob\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "items", &items_array)) {
        fprintf(stderr, "Invalid cache format\n");
        json_object_put(parsed_json);
        return;
    }

    array_length = json_object_array_length(items_array);
    for (i = 0; i < array_length; i++) {
        struct json_object *item_obj = json_object_array_get_idx(items_array, i);
        struct json_object *key_obj, *value_obj;

        if (!json_object_object_get_ex(item_obj, "key", &key_obj) ||
            !json_object_object_get_ex(item_obj, "value", &value_obj)) {
            continue;
        }

        strncpy(item.key, json_object_get_string(key_obj), sizeof(item.key) - 1);
        strncpy(item.value, json_object_get_string(value_obj), sizeof(item.value) - 1);

        printf("Cache Item - Key: %s, Value: %s\n", item.key, item.value);
    }

    json_object_put(parsed_json);
}

int main() {
    char blob[MAX_BLOB_SIZE];
    printf("Enter cache blob data: ");
    fgets(blob, sizeof(blob), stdin);

    restore_cache(blob);

    return 0;
}