#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *preference_name;
    char *value;
    int active;
} Preference;

void apply_preference(Preference *preference) {
    printf("Preference: %s, Value: %s, Active: %d\n", preference->preference_name, preference->value, preference->active);
}

int main() {
    const char *json_str = "{\"preference_name\":\"Theme\", \"value\":\"Dark\", \"active\":1}";
    struct json_object *parsed_json;
    struct json_object *preference_name_obj, *value_obj, *active_obj;
    Preference preference;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj) ||
        !json_object_object_get_ex(parsed_json, "value", &value_obj) ||
        !json_object_object_get_ex(parsed_json, "active", &active_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    preference.preference_name = strdup(json_object_get_string(preference_name_obj));
    preference.value = strdup(json_object_get_string(value_obj));
    preference.active = json_object_get_int(active_obj);

    apply_preference(&preference);

    free(preference.preference_name);
    free(preference.value);
    json_object_put(parsed_json);

    return 0;
}