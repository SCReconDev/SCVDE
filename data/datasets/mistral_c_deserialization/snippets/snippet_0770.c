#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* pref_name;
    char* pref_value;
} Preference;

void deserialize_preference(const char* json_str, Preference* preference) {
    struct json_object* parsed_json;
    struct json_object* pref_name_obj;
    struct json_object* pref_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "pref_name", &pref_name_obj)) {
        fprintf(stderr, "Error getting pref_name from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "pref_value", &pref_value_obj)) {
        fprintf(stderr, "Error getting pref_value from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    preference->pref_name = strdup(json_object_get_string(pref_name_obj));
    preference->pref_value = strdup(json_object_get_string(pref_value_obj));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"pref_name\":\"theme\",\"pref_value\":\"dark\"}";
    Preference preference;

    deserialize_preference(json_str, &preference);

    printf("Preference Name: %s\n", preference.pref_name);
    printf("Preference Value: %s\n", preference.pref_value);

    free(preference.pref_name);
    free(preference.pref_value);

    return 0;
}