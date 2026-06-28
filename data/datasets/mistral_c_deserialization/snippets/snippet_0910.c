#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} UserPreference;

void import_preference(UserPreference* preference) {
    printf("Importing preference: %s with value: %s\n", preference->preference_name, preference->preference_value);
}

int main() {
    const char* user_file = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    cJSON* json = cJSON_Parse(user_file);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    UserPreference preference;
    cJSON* preference_name = cJSON_GetObjectItemCaseSensitive(json, "preference_name");
    if (cJSON_IsString(preference_name) && (preference_name->valuestring != NULL)) {
        preference.preference_name = strdup(preference_name->valuestring);
    } else {
        fprintf(stderr, "Invalid preference name in user file\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* preference_value = cJSON_GetObjectItemCaseSensitive(json, "preference_value");
    if (cJSON_IsString(preference_value) && (preference_value->valuestring != NULL)) {
        preference.preference_value = strdup(preference_value->valuestring);
    } else {
        fprintf(stderr, "Invalid preference value in user file\n");
        free(preference.preference_name);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    import_preference(&preference);
    free(preference.preference_name);
    free(preference.preference_value);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}