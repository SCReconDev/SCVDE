#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_name;
    char* value;
    int active;
} Preference;

void print_preference(Preference* preference) {
    printf("Preference Name: %s\n", preference->preference_name);
    printf("Value: %s\n", preference->value);
    printf("Active: %d\n", preference->active);
}

int main() {
    const char* json_str = "{\"preference_name\":\"Dark Mode\",\"value\":\"Enabled\",\"active\":1}";
    struct json_object* parsed_json;
    struct json_object* preference_name;
    struct json_object* value;
    struct json_object* active;
    Preference preference;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "preference_name", &preference_name);
    json_object_object_get_ex(parsed_json, "value", &value);
    json_object_object_get_ex(parsed_json, "active", &active);

    if (preference_name == NULL || value == NULL || active == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    preference.preference_name = strdup(json_object_get_string(preference_name));
    preference.value = strdup(json_object_get_string(value));
    preference.active = json_object_get_int(active);

    print_preference(&preference);

    free(preference.preference_name);
    free(preference.value);
    json_object_put(parsed_json);

    return 0;
}