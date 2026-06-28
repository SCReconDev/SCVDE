#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *preference_name;
    char *preference_value;
} PreferenceData;

void deserialize_preference_data(const char *json_str, PreferenceData *preference_data) {
    struct json_object *parsed_json;
    struct json_object *preference_name_obj, *preference_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj);

    if (preference_name_obj != NULL && json_object_get_type(preference_name_obj) == json_type_string) {
        preference_data->preference_name = strdup(json_object_get_string(preference_name_obj));
    }

    if (preference_value_obj != NULL && json_object_get_type(preference_value_obj) == json_type_string) {
        preference_data->preference_value = strdup(json_object_get_string(preference_value_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    PreferenceData preference_data;

    deserialize_preference_data(json_str, &preference_data);

    printf("Preference Name: %s\n", preference_data.preference_name);
    printf("Preference Value: %s\n", preference_data.preference_value);

    free(preference_data.preference_name);
    free(preference_data.preference_value);
    return 0;
}