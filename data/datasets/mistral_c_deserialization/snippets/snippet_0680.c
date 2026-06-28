#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} PreferenceData;

void import_preference(PreferenceData* preference) {
    printf("Preference Name: %s, Preference Value: %s\n", preference->preference_name, preference->preference_value);
}

int main() {
    const char* user_file = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    struct json_object* json_obj = json_tokener_parse(user_file);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    PreferenceData preference;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "preference_name") == 0) {
            preference.preference_name = strdup(json_object_get_string(val));
        } else if (strcmp(key, "preference_value") == 0) {
            preference.preference_value = strdup(json_object_get_string(val));
        }
    }

    import_preference(&preference);
    free(preference.preference_name);
    free(preference.preference_value);
    json_object_put(json_obj);

    return 0;
}