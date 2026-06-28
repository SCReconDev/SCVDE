#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference;
    int value;
} UserPreference;

void deserialize_user_preference(const char* json_str, UserPreference* preference) {
    struct json_object* parsed_json;
    struct json_object* preference_name;
    struct json_object* value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "preference", &preference_name);
    json_object_object_get_ex(parsed_json, "value", &value);

    if (preference_name != NULL && json_object_get_type(preference_name) == json_type_string) {
        preference->preference = strdup(json_object_get_string(preference_name));
    }

    if (value != NULL && json_object_get_type(value) == json_type_int) {
        preference->value = json_object_get_int(value);
    }

    json_object_put(parsed_json);
}

void import_preferences(const char* user_file) {
    UserPreference preference = {NULL, 0};
    deserialize_user_preference(user_file, &preference);

    if (preference.preference != NULL) {
        printf("Preference: %s\n", preference.preference);
        free(preference.preference);
    }

    printf("Value: %d\n", preference.value);
}

int main() {
    const char* user_file = "{\"preference\":\"theme\",\"value\":1}";
    import_preferences(user_file);
    return 0;
}