#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *preference_name;
    char *preference_value;
} UserPreference;

void apply_preference(UserPreference *preference) {
    printf("Applying preference: %s\n", preference->preference_name);
    printf("Value: %s\n", preference->preference_value);
}

int main() {
    const char *user_file = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    struct json_object *parsed_json;
    struct json_object *preference_name;
    struct json_object *preference_value;
    UserPreference preference;

    parsed_json = json_tokener_parse(user_file);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "preference_name", &preference_name);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value);

    if (preference_name == NULL || preference_value == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    preference.preference_name = strdup(json_object_get_string(preference_name));
    preference.preference_value = strdup(json_object_get_string(preference_value));

    apply_preference(&preference);

    free(preference.preference_name);
    free(preference.preference_value);
    json_object_put(parsed_json);

    return 0;
}