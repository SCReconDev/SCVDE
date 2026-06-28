#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char preference_name[50];
    char preference_value[100];
} Preference;

int deserialize_preference(const char* json_str, Preference* preference) {
    struct json_object *parsed_json;
    struct json_object *preference_name_obj, *preference_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj)) {
        fprintf(stderr, "Error getting preference_name\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj)) {
        fprintf(stderr, "Error getting preference_value\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(preference->preference_name, json_object_get_string(preference_name_obj), sizeof(preference->preference_name) - 1);
    strncpy(preference->preference_value, json_object_get_string(preference_value_obj), sizeof(preference->preference_value) - 1);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    Preference preference;

    printf("Enter preference JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_preference(buffer, &preference) == 0) {
        printf("Deserialized Preference: Name=%s, Value=%s\n", preference.preference_name, preference.preference_value);
    } else {
        fprintf(stderr, "Failed to deserialize preference\n");
    }

    return 0;
}