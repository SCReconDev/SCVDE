#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char preference_id[50];
    char preference_name[100];
    char preference_value[200];
} Preference;

int validate_preference_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *preference_id_obj, *preference_name_obj, *preference_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_id", &preference_id_obj) ||
        !json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj) ||
        !json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(preference_id_obj) != json_type_string ||
        json_object_get_type(preference_name_obj) != json_type_string ||
        json_object_get_type(preference_value_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

Preference* deserialize_preference(const char *json_str) {
    Preference *preference = malloc(sizeof(Preference));
    if (!preference) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *preference_id_obj, *preference_name_obj, *preference_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(preference);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "preference_id", &preference_id_obj);
    json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj);

    strncpy(preference->preference_id, json_object_get_string(preference_id_obj), sizeof(preference->preference_id) - 1);
    strncpy(preference->preference_name, json_object_get_string(preference_name_obj), sizeof(preference->preference_name) - 1);
    strncpy(preference->preference_value, json_object_get_string(preference_value_obj), sizeof(preference->preference_value) - 1);

    json_object_put(parsed_json);
    return preference;
}

void process_preference_data(const char *json_str) {
    if (!validate_preference_json(json_str)) {
        printf("Invalid preference data format\n");
        return;
    }

    Preference *preference = deserialize_preference(json_str);
    if (!preference) {
        printf("Failed to deserialize preference data\n");
        return;
    }

    printf("Preference ID: %s, Preference Name: %s, Preference Value: %s\n", preference->preference_id, preference->preference_name, preference->preference_value);
    free(preference);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter preference data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_preference_data(buffer);

    return 0;
}