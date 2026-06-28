#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} Preference;

void deserialize_preference(const char* json_str, Preference* pref) {
    struct json_object* parsed_json;
    struct json_object* preference_name;
    struct json_object* preference_value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_name", &preference_name)) {
        fprintf(stderr, "Error: 'preference_name' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_value", &preference_value)) {
        fprintf(stderr, "Error: 'preference_value' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    pref->preference_name = strdup(json_object_get_string(preference_name));
    pref->preference_value = strdup(json_object_get_string(preference_value));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    Preference pref;

    deserialize_preference(json_str, &pref);

    printf("Preference Name: %s\n", pref.preference_name);
    printf("Preference Value: %s\n", pref.preference_value);

    free(pref.preference_name);
    free(pref.preference_value);
    return 0;
}