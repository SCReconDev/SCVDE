#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* preference_id;
    char* value;
    char* description;
} Preference;

bool validate_preference_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "preference_id") ||
        !cJSON_HasObjectItem(json, "value") ||
        !cJSON_HasObjectItem(json, "description")) {
        return false;
    }

    cJSON* preference_id = cJSON_GetObjectItemCaseSensitive(json, "preference_id");
    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");

    if (!cJSON_IsString(preference_id) || !cJSON_IsString(value) || !cJSON_IsString(description)) {
        return false;
    }

    return true;
}

Preference* deserialize_preference(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_preference_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Preference* pref = (Preference*)malloc(sizeof(Preference));
    if (!pref) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* preference_id = cJSON_GetObjectItemCaseSensitive(json, "preference_id");
    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");

    pref->preference_id = strdup(preference_id->valuestring);
    pref->value = strdup(value->valuestring);
    pref->description = strdup(description->valuestring);

    cJSON_Delete(json);

    return pref;
}

void free_preference(Preference* pref) {
    if (pref) {
        free(pref->preference_id);
        free(pref->value);
        free(pref->description);
        free(pref);
    }
}

int main() {
    const char* json_str = "{\"preference_id\":\"pref123\",\"value\":\"dark\",\"description\":\"Theme preference\"}";
    Preference* pref = deserialize_preference(json_str);

    if (pref) {
        printf("Preference ID: %s\n", pref->preference_id);
        printf("Value: %s\n", pref->value);
        printf("Description: %s\n", pref->description);
        free_preference(pref);
    } else {
        printf("Failed to deserialize preference.\n");
    }

    return 0;
}