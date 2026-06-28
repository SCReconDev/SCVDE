#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char cache_key[50];
    char cache_value[50];
    int ttl;
} CacheItem;

int validate_cache_item(CacheItem *item) {
    if (strlen(item->cache_key) == 0 || strlen(item->cache_value) == 0 || item->ttl <= 0) {
        return 0;
    }
    return 1;
}

CacheItem* deserialize_cache_item(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *cache_key_obj, *cache_value_obj, *ttl_obj;
    CacheItem *item = (CacheItem*)malloc(sizeof(CacheItem));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(item);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "cache_key", &cache_key_obj);
    json_object_object_get_ex(parsed_json, "cache_value", &cache_value_obj);
    json_object_object_get_ex(parsed_json, "ttl", &ttl_obj);

    if (cache_key_obj == NULL || cache_value_obj == NULL || ttl_obj == NULL) {
        json_object_put(parsed_json);
        free(item);
        return NULL;
    }

    strncpy(item->cache_key, json_object_get_string(cache_key_obj), sizeof(item->cache_key) - 1);
    strncpy(item->cache_value, json_object_get_string(cache_value_obj), sizeof(item->cache_value) - 1);
    item->ttl = json_object_get_int(ttl_obj);

    json_object_put(parsed_json);

    if (!validate_cache_item(item)) {
        free(item);
        return NULL;
    }

    return item;
}

void process_cache_item(CacheItem *item) {
    printf("Cache Key: %s\n", item->cache_key);
    printf("Cache Value: %s\n", item->cache_value);
    printf("TTL: %d\n", item->ttl);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    CacheItem *item;

    printf("Enter cache item data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    item = deserialize_cache_item(json_str);
    if (item == NULL) {
        printf("Invalid cache item data\n");
        return 1;
    }

    process_cache_item(item);
    free(item);

    return 0;
}