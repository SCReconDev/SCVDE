#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char preference_name[MAX_BUFFER_SIZE];
    char preference_value[MAX_BUFFER_SIZE];
} UserPreference;

void import_user_preference(const char *json_str, UserPreference *preference) {
    struct json_object *parsed_json;
    struct json_object *preference_name_obj;
    struct json_object *preference_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj);
    if (preference_name_obj != NULL) {
        strncpy(preference->preference_name, json_object_get_string(preference_name_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj);
    if (preference_value_obj != NULL) {
        strncpy(preference->preference_value, json_object_get_string(preference_value_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    UserPreference preference;

    import_user_preference(json_str, &preference);

    printf("Preference Name: %s\n", preference.preference_name);
    printf("Preference Value: %s\n", preference.preference_value);

    return 0;
}