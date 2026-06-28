#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void restore_cache(const char* blob) {
    cJSON* json = cJSON_Parse(blob);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* key = cJSON_GetObjectItemCaseSensitive(json, "key");
    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");

    if (cJSON_IsString(key) && (key->valuestring != NULL) && cJSON_IsString(value) && (value->valuestring != NULL)) {
        CacheItem item;
        item.key = strdup(key->valuestring);
        item.value = strdup(value->valuestring);

        printf("Cache Item: %s, Value: %s\n", item.key, item.value);

        free(item.key);
        free(item.value);
    }

    cJSON_Delete(json);
}

int main() {
    const char* blob = "{\"key\":\"user_prefs\",\"value\":\"dark_mode\"}";
    restore_cache(blob);
    return 0;
}