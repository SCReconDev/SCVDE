#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* key;
    char* value;
} CacheItem;

void parse_cache_blob(const char* blob) {
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

    if (cJSON_IsString(key) && (key->valuestring != NULL)) {
        printf("Key: %s\n", key->valuestring);
    }

    if (cJSON_IsString(value) && (value->valuestring != NULL)) {
        printf("Value: %s\n", value->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* blob = "{\"key\":\"cache_key\",\"value\":\"cache_value\"}";
    parse_cache_blob(blob);
    return 0;
}