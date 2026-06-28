#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

bool validate_cache_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_key = json_object_object_get_ex(obj, "key", NULL);
    bool has_value = json_object_object_get_ex(obj, "value", NULL);

    json_object_put(obj);
    return has_key && has_value;
}

CacheItem* deserialize_cache_item(const char* json_str) {
    if (!validate_cache_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    CacheItem* item = malloc(sizeof(CacheItem));

    struct json_object* key_obj;
    json_object_object_get_ex(obj, "key", &key_obj);
    item->key = strdup(json_object_get_string(key_obj));

    struct json_object* value_obj;
    json_object_object_get_ex(obj, "value", &value_obj);
    item->value = strdup(json_object_get_string(value_obj));

    json_object_put(obj);
    return item;
}

void free_cache_item(CacheItem* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void restore_cache(const char* json_str) {
    CacheItem* item = deserialize_cache_item(json_str);
    if (item == NULL) {
        printf("Invalid cache data\n");
        return;
    }

    printf("Cache Key: %s, Cache Value: %s\n", item->key, item->value);
    free_cache_item(item);
}

int main() {
    const char* json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode\"}";
    restore_cache(json_str);
    return 0;
}