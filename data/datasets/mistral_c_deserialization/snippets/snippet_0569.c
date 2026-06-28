#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char fixture_id[50];
    char fixture_name[50];
    char fixture_data[100];
} FixtureInfo;

int validate_fixture_info(FixtureInfo *fixture_info) {
    if (strlen(fixture_info->fixture_id) == 0 || strlen(fixture_info->fixture_name) == 0 || strlen(fixture_info->fixture_data) == 0) {
        return 0;
    }
    return 1;
}

FixtureInfo* deserialize_fixture_info(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *fixture_id_obj, *fixture_name_obj, *fixture_data_obj;
    FixtureInfo *fixture_info = (FixtureInfo*)malloc(sizeof(FixtureInfo));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(fixture_info);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "fixture_id", &fixture_id_obj);
    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj);
    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj);

    if (fixture_id_obj == NULL || fixture_name_obj == NULL || fixture_data_obj == NULL) {
        json_object_put(parsed_json);
        free(fixture_info);
        return NULL;
    }

    strncpy(fixture_info->fixture_id, json_object_get_string(fixture_id_obj), sizeof(fixture_info->fixture_id) - 1);
    strncpy(fixture_info->fixture_name, json_object_get_string(fixture_name_obj), sizeof(fixture_info->fixture_name) - 1);
    strncpy(fixture_info->fixture_data, json_object_get_string(fixture_data_obj), sizeof(fixture_info->fixture_data) - 1);

    json_object_put(parsed_json);

    if (!validate_fixture_info(fixture_info)) {
        free(fixture_info);
        return NULL;
    }

    return fixture_info;
}

void process_fixture_info(FixtureInfo *fixture_info) {
    printf("Fixture ID: %s\n", fixture_info->fixture_id);
    printf("Fixture Name: %s\n", fixture_info->fixture_name);
    printf("Fixture Data: %s\n", fixture_info->fixture_data);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    FixtureInfo *fixture_info;

    printf("Enter fixture info data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    fixture_info = deserialize_fixture_info(json_str);
    if (fixture_info == NULL) {
        printf("Invalid fixture info data\n");
        return 1;
    }

    process_fixture_info(fixture_info);
    free(fixture_info);

    return 0;
}