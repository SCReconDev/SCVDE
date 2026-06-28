#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* key;
    char* value;
} CacheEntry;

void restore_cache(CacheEntry* entry) {
    printf("Restored cache entry - Key: %s, Value: %s\n", entry->key, entry->value);
}

int main() {
    const char* blob = "{\"key\":\"config\",\"value\":\"settings\"}";
    cJSON* json = cJSON_Parse(blob);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    CacheEntry entry;
    cJSON* key = cJSON_GetObjectItemCaseSensitive(json, "key");
    if (cJSON_IsString(key) && (key->valuestring != NULL)) {
        entry.key = strdup(key->valuestring);
    } else {
        fprintf(stderr, "Invalid key in blob\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");
    if (cJSON_IsString(value) && (value->valuestring != NULL)) {
        entry.value = strdup(value->valuestring);
    } else {
        fprintf(stderr, "Invalid value in blob\n");
        free(entry.key);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    restore_cache(&entry);
    free(entry.key);
    free(entry.value);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}