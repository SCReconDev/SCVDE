#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *preference_name;
    char *preference_value;
    char *user_id;
} Preference;

void parse_preference_data(const char *json_str, Preference *preference) {
    struct json_object *parsed_json;
    struct json_object *name_obj;
    struct json_object *value_obj;
    struct json_object *user_id_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "preference_name", &name_obj)) {
        preference->preference_name = strdup(json_object_get_string(name_obj));
    }

    if (json_object_object_get_ex(parsed_json, "preference_value", &value_obj)) {
        preference->preference_value = strdup(json_object_get_string(value_obj));
    }

    if (json_object_object_get_ex(parsed_json, "user_id", &user_id_obj)) {
        preference->user_id = strdup(json_object_get_string(user_id_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\",\"user_id\":\"U789\"}";
    Preference preference;

    parse_preference_data(json_str, &preference);

    printf("Preference Name: %s\n", preference.preference_name);
    printf("Preference Value: %s\n", preference.preference_value);
    printf("User ID: %s\n", preference.user_id);

    free(preference.preference_name);
    free(preference.preference_value);
    free(preference.user_id);
    return 0;
}