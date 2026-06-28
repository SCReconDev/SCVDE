#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} Preference;

void parse_preference_data(const char* data) {
    cJSON* json = cJSON_Parse(data);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* preference_name = cJSON_GetObjectItemCaseSensitive(json, "preference_name");
    cJSON* preference_value = cJSON_GetObjectItemCaseSensitive(json, "preference_value");

    if (cJSON_IsString(preference_name) && (preference_name->valuestring != NULL)) {
        printf("Preference Name: %s\n", preference_name->valuestring);
    }

    if (cJSON_IsString(preference_value) && (preference_value->valuestring != NULL)) {
        printf("Preference Value: %s\n", preference_value->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* data = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    parse_preference_data(data);
    return 0;
}