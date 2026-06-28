#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char preference_id[50];
    char preference_name[50];
    char preference_value[100];
} PreferenceInfo;

int validate_preference_info(PreferenceInfo *preference_info) {
    if (strlen(preference_info->preference_id) == 0 || strlen(preference_info->preference_name) == 0 || strlen(preference_info->preference_value) == 0) {
        return 0;
    }
    return 1;
}

PreferenceInfo* deserialize_preference_info(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *preference_id_obj, *preference_name_obj, *preference_value_obj;
    PreferenceInfo *preference_info = (PreferenceInfo*)malloc(sizeof(PreferenceInfo));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(preference_info);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "preference_id", &preference_id_obj);
    json_object_object_get_ex(parsed_json, "preference_name", &preference_name_obj);
    json_object_object_get_ex(parsed_json, "preference_value", &preference_value_obj);

    if (preference_id_obj == NULL || preference_name_obj == NULL || preference_value_obj == NULL) {
        json_object_put(parsed_json);
        free(preference_info);
        return NULL;
    }

    strncpy(preference_info->preference_id, json_object_get_string(preference_id_obj), sizeof(preference_info->preference_id) - 1);
    strncpy(preference_info->preference_name, json_object_get_string(preference_name_obj), sizeof(preference_info->preference_name) - 1);
    strncpy(preference_info->preference_value, json_object_get_string(preference_value_obj), sizeof(preference_info->preference_value) - 1);

    json_object_put(parsed_json);

    if (!validate_preference_info(preference_info)) {
        free(preference_info);
        return NULL;
    }

    return preference_info;
}

void process_preference_info(PreferenceInfo *preference_info) {
    printf("Preference ID: %s\n", preference_info->preference_id);
    printf("Preference Name: %s\n", preference_info->preference_name);
    printf("Preference Value: %s\n", preference_info->preference_value);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    PreferenceInfo *preference_info;

    printf("Enter preference info data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    preference_info = deserialize_preference_info(json_str);
    if (preference_info == NULL) {
        printf("Invalid preference info data\n");
        return 1;
    }

    process_preference_info(preference_info);
    free(preference_info);

    return 0;
}