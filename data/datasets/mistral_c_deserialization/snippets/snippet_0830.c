#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *preference_id;
    char *value;
} Preference;

void parse_preference(json_object *jobj, Preference *preference) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "preference_id") == 0) {
            preference->preference_id = strdup(json_object_get_string(val));
        } else if (strcmp(key, "value") == 0) {
            preference->value = strdup(json_object_get_string(val));
        }
    }
}

int main() {
    const char *user_file = "{\"preference_id\":\"pref123\",\"value\":\"dark mode\"}";
    json_object *jobj = json_tokener_parse(user_file);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Preference preference;
    parse_preference(jobj, &preference);

    printf("Preference ID: %s\n", preference.preference_id);
    printf("Value: %s\n", preference.value);

    free(preference.preference_id);
    free(preference.value);
    json_object_put(jobj);

    return 0;
}