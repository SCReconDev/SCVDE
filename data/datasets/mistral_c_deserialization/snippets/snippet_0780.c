#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *preference_name;
    char *preference_value;
} Preference;

void parse_preference(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *preference_name;
    struct json_object *preference_value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_name", &preference_name)) {
        fprintf(stderr, "Preference name not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_value", &preference_value)) {
        fprintf(stderr, "Preference value not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    Preference preference;
    preference.preference_name = strdup(json_object_get_string(preference_name));
    preference.preference_value = strdup(json_object_get_string(preference_value));

    printf("Preference Name: %s, Preference Value: %s\n", preference.preference_name, preference.preference_value);

    free(preference.preference_name);
    free(preference.preference_value);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    parse_preference(json_str);
    return 0;
}