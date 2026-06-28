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
    struct json_object* name_obj;
    struct json_object* value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "value", &value_obj);

    if (name_obj != NULL && json_object_is_type(name_obj, json_type_string)) {
        preference->preference_name = strdup(json_object_get_string(name_obj));
    }

    if (value_obj != NULL && json_object_is_type(value_obj, json_type_string)) {
        preference->preference_value = strdup(json_object_get_string(value_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"name\":\"theme\",\"value\":\"dark\"}";
    Preference preference;

    deserialize_preference(json_str, &preference);

    printf("Preference Name: %s\n", preference.preference_name);
    printf("Preference Value: %s\n", preference.preference_value);

    free(preference.preference_name);
    free(preference.preference_value);
    return 0;
}