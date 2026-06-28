#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char preference_name[MAX_BUFFER_SIZE];
    char preference_value[MAX_BUFFER_SIZE];
} Preference;

void import_user_preferences(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *preference_name_obj, *preference_value_obj;
    Preference preference;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj) ||
        !json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(preference.preference_name, json_object_get_string(preference_name_obj), MAX_BUFFER_SIZE - 1);
    strncpy(preference.preference_value, json_object_get_string(preference_value_obj), MAX_BUFFER_SIZE - 1);

    printf("Preference Name: %s, Preference Value: %s\n", preference.preference_name, preference.preference_value);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    import_user_preferences(json_data);
    return 0;
}