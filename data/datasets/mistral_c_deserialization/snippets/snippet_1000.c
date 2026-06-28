#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FILE_SIZE 1024

typedef struct {
    char preference_id[256];
    int preference_value;
    char preference_data[256];
} Preference;

void deserialize_preference(Preference *preference, const char *file_content) {
    struct json_object *parsed_json;
    struct json_object *preference_id_obj, *preference_value_obj, *preference_data_obj;

    parsed_json = json_tokener_parse(file_content);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON file content\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "preference_id", &preference_id_obj);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj);
    json_object_object_get_ex(parsed_json, "preference_data", &preference_data_obj);

    if (preference_id_obj != NULL && json_object_is_type(preference_id_obj, json_type_string)) {
        strncpy(preference->preference_id, json_object_get_string(preference_id_obj), sizeof(preference->preference_id) - 1);
    }

    if (preference_value_obj != NULL && json_object_is_type(preference_value_obj, json_type_int)) {
        preference->preference_value = json_object_get_int(preference_value_obj);
    }

    if (preference_data_obj != NULL && json_object_is_type(preference_data_obj, json_type_string)) {
        strncpy(preference->preference_data, json_object_get_string(preference_data_obj), sizeof(preference->preference_data) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    Preference preference;
    char file_content[MAX_FILE_SIZE];
    FILE *file;
    char filename[256];

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    fread(file_content, sizeof(char), sizeof(file_content), file);
    fclose(file);

    deserialize_preference(&preference, file_content);

    printf("Deserialized Preference:\n");
    printf("Preference ID: %s\n", preference.preference_id);
    printf("Preference Value: %d\n", preference.preference_value);
    printf("Preference Data: %s\n", preference.preference_data);

    return 0;
}