#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char preference_id[256];
    char preference_name[256];
    char preference_value[256];
} Preference;

int validate_preference(Preference *preference) {
    if (strlen(preference->preference_id) == 0 || strlen(preference->preference_name) == 0 || strlen(preference->preference_value) == 0) {
        return 0;
    }
    return 1;
}

Preference* deserialize_preference(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *preference_id_obj, *preference_name_obj, *preference_value_obj;
    Preference *preference = malloc(sizeof(Preference));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(preference);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "preference_id", &preference_id_obj);
    json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj);

    if (preference_id_obj == NULL || preference_name_obj == NULL || preference_value_obj == NULL) {
        json_object_put(parsed_json);
        free(preference);
        return NULL;
    }

    strncpy(preference->preference_id, json_object_get_string(preference_id_obj), sizeof(preference->preference_id) - 1);
    strncpy(preference->preference_name, json_object_get_string(preference_name_obj), sizeof(preference->preference_name) - 1);
    strncpy(preference->preference_value, json_object_get_string(preference_value_obj), sizeof(preference->preference_value) - 1);

    json_object_put(parsed_json);

    if (!validate_preference(preference)) {
        free(preference);
        return NULL;
    }

    return preference;
}

void process_preference(Preference *preference) {
    printf("Processing preference: %s, %s, %s\n", preference->preference_id, preference->preference_name, preference->preference_value);
}

int main() {
    char input[MAX_INPUT_SIZE];
    Preference *preference;

    printf("Enter preference data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    preference = deserialize_preference(input);
    if (preference == NULL) {
        printf("Invalid preference data\n");
        return 1;
    }

    process_preference(preference);

    free(preference);
    return 0;
}