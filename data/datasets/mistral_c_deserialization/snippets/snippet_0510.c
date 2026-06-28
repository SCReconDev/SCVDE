#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* preference_name;
    char* value;
} Preference;

void import_preferences(const char* user_file) {
    cJSON* json = cJSON_Parse(user_file);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* preference_name = cJSON_GetObjectItemCaseSensitive(json, "preference_name");
    cJSON* value = cJSON_GetObjectItemCaseSensitive(json, "value");

    if (cJSON_IsString(preference_name) && (preference_name->valuestring != NULL) && cJSON_IsString(value) && (value->valuestring != NULL)) {
        Preference pref;
        pref.preference_name = strdup(preference_name->valuestring);
        pref.value = strdup(value->valuestring);

        printf("Preference: %s, Value: %s\n", pref.preference_name, pref.value);

        free(pref.preference_name);
        free(pref.value);
    }

    cJSON_Delete(json);
}

int main() {
    const char* user_file = "{\"preference_name\":\"theme\",\"value\":\"dark\"}";
    import_preferences(user_file);
    return 0;
}