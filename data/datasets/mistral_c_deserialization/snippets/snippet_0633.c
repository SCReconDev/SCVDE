#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

bool validate_cache_item_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "key") ||
        !cJSON_HasObjectItem(json, "value")) {
        return false;
    }

    cJSON* key = cJSON_GetObjectItemCaseSensitive(json, "key");
    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");

    if (!cJSON_IsString(key) || !cJSON_IsString(value)) {
        return false;
    }

    return true;
}

CacheItem* deserialize_cache_item(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_cache_item_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    CacheItem* item = (CacheItem*)malloc(sizeof(CacheItem));
    if (!item) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* key = cJSON_GetObjectItemCaseSensitive(json, "key");
    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");

    item->key = strdup(key->valuestring);
    item->value = strdup(value->valuestring);

    cJSON_Delete(json);

    return item;
}

void free_cache_item(CacheItem* item) {
    if (item) {
        free(item->key);
        free(item->value);
        free(item);
    }
}

int main() {
    const char* json_str = "{\"key\":\"item1\",\"value\":\"data123\"}";
    CacheItem* item = deserialize_cache_item(json_str);

    if (item) {
        printf("Key: %s\n", item->key);
        printf("Value: %s\n", item->value);
        free_cache_item(item);
    } else {
        printf("Failed to deserialize cache item.\n");
    }

    return 0;
}