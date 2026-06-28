#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} PreferenceData;

void deserialize_preference_data(const char* json_str, PreferenceData* preference_data) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* preference_name = cJSON_GetObjectItemCaseSensitive(json, "preference_name");
    if (cJSON_IsString(preference_name) && (preference_name->valuestring != NULL)) {
        preference_data->preference_name = strdup(preference_name->valuestring);
    }

    cJSON* preference_value = cJSON_GetObjectItemCaseSensitive(json, "preference_value");
    if (cJSON_IsString(preference_value) && (preference_value->valuestring != NULL)) {
        preference_data->preference_value = strdup(preference_value->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    PreferenceData preference_data;

    deserialize_preference_data(json_str, &preference_data);

    printf("Preference Name: %s\n", preference_data.preference_name);
    printf("Preference Value: %s\n", preference_data.preference_value);

    free(preference_data.preference_name);
    free(preference_data.preference_value);

    return 0;
}