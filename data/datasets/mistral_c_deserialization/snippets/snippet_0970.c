#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} Preference;

void deserialize_preference(const char* json_str, Preference* preference) {
    struct json_object* parsed_json;
    struct json_object* preference_name;
    struct json_object* preference_value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "preference_name", &preference_name);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value);

    if (preference_name != NULL && json_object_is_type(preference_name, json_type_string)) {
        preference->preference_name = strdup(json_object_get_string(preference_name));
    }

    if (preference_value != NULL && json_object_is_type(preference_value, json_type_string)) {
        preference->preference_value = strdup(json_object_get_string(preference_value));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    Preference preference;

    deserialize_preference(json_str, &preference);

    printf("Preference Name: %s\n", preference.preference_name);
    printf("Preference Value: %s\n", preference.preference_value);

    free(preference.preference_name);
    free(preference.preference_value);
    return 0;
}