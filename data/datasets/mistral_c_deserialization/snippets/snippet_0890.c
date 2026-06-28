#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_name;
    char* preference_value;
} UserPreference;

void process_user_preference(UserPreference* pref) {
    printf("Preference Name: %s, Preference Value: %s\n", pref->preference_name, pref->preference_value);
}

int main() {
    const char* user_file = "{\"preference_name\":\"theme\",\"preference_value\":\"dark\"}";
    struct json_object* parsed_json;
    struct json_object* preference_name_obj;
    struct json_object* preference_value_obj;
    UserPreference pref;

    parsed_json = json_tokener_parse(user_file);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj) ||
        !json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    pref.preference_name = strdup(json_object_get_string(preference_name_obj));
    pref.preference_value = strdup(json_object_get_string(preference_value_obj));

    process_user_preference(&pref);

    free(pref.preference_name);
    free(pref.preference_value);
    json_object_put(parsed_json);

    return 0;
}