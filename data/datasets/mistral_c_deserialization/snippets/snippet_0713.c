#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void deserialize_cache_item(const char* json_str, CacheItem* item) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* key = cJSON_GetObjectItemCaseSensitive(json, "key");
    if (cJSON_IsString(key) && (key->valuestring != NULL)) {
        item->key = strdup(key->valuestring);
    }

    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");
    if (cJSON_IsString(value) && (value->valuestring != NULL)) {
        item->value = strdup(value->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"key\":\"user_prefs\",\"value\":\"dark_mode=true\"}";
    CacheItem item;

    deserialize_cache_item(json_str, &item);

    printf("Key: %s\n", item.key);
    printf("Value: %s\n", item.value);

    free(item.key);
    free(item.value);

    return 0;
}