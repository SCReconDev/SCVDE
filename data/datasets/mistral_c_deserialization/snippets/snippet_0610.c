#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* preference_id;
    char* preference_value;
} Preference;

void process_preference(Preference* preference) {
    printf("Preference ID: %s\n", preference->preference_id);
    printf("Preference Value: %s\n", preference->preference_value);
}

Preference* deserialize_preference(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* preference_id_obj;
    struct json_object* preference_value_obj;
    Preference* preference = malloc(sizeof(Preference));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(preference);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "preference_id", &preference_id_obj);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj);

    if (preference_id_obj == NULL || preference_value_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(preference);
        return NULL;
    }

    preference->preference_id = strdup(json_object_get_string(preference_id_obj));
    preference->preference_value = strdup(json_object_get_string(preference_value_obj));

    json_object_put(parsed_json);
    return preference;
}

int main() {
    const char* json_str = "{\"preference_id\":\"theme\",\"preference_value\":\"dark\"}";
    Preference* preference = deserialize_preference(json_str);

    if (preference != NULL) {
        process_preference(preference);
        free(preference->preference_id);
        free(preference->preference_value);
        free(preference);
    }

    return 0;
}