#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_id;
    char* value;
} Preference;

void load_preference(const char* json_str, Preference* pref) {
    struct json_object* parsed_json;
    struct json_object* preference_id;
    struct json_object* value;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_id", &preference_id)) {
        fprintf(stderr, "Error: 'preference_id' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "value", &value)) {
        fprintf(stderr, "Error: 'value' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    pref->preference_id = strdup(json_object_get_string(preference_id));
    pref->value = strdup(json_object_get_string(value));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"preference_id\":\"pref123\",\"value\":\"dark mode\"}";
    Preference pref;

    load_preference(json_str, &pref);

    printf("Preference ID: %s\n", pref.preference_id);
    printf("Value: %s\n", pref.value);

    free(pref.preference_id);
    free(pref.value);
    return 0;
}