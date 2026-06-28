#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *key;
    char *value;
} CacheItem;

void restore_cache(const char *blob, CacheItem *items, int *count) {
    struct json_object *parsed_json;
    struct json_object *items_array;
    size_t i;

    parsed_json = json_tokener_parse(blob);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "items", &items_array)) {
        *count = json_object_array_length(items_array);
        for (i = 0; i < *count; i++) {
            struct json_object *item_obj = json_object_array_get_idx(items_array, i);
            struct json_object *key_obj;
            struct json_object *value_obj;

            if (json_object_object_get_ex(item_obj, "key", &key_obj)) {
                items[i].key = strdup(json_object_get_string(key_obj));
            }

            if (json_object_object_get_ex(item_obj, "value", &value_obj)) {
                items[i].value = strdup(json_object_get_string(value_obj));
            }
        }
    }

    json_object_put(parsed_json);
}

int main() {
    const char *blob = "{\"items\":[{\"key\":\"item1\",\"value\":\"value1\"},{\"key\":\"item2\",\"value\":\"value2\"}]}";
    CacheItem items[10];
    int count = 0;
    int i;

    restore_cache(blob, items, &count);

    for (i = 0; i < count; i++) {
        printf("Key: %s, Value: %s\n", items[i].key, items[i].value);
        free(items[i].key);
        free(items[i].value);
    }

    return 0;
}