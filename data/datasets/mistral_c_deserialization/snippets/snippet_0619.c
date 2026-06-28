#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char fixture_id[50];
    char fixture_name[100];
    char fixture_data[200];
} Fixture;

int validate_fixture_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *fixture_id_obj, *fixture_name_obj, *fixture_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_id", &fixture_id_obj) ||
        !json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj) ||
        !json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(fixture_id_obj) != json_type_string ||
        json_object_get_type(fixture_name_obj) != json_type_string ||
        json_object_get_type(fixture_data_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

Fixture* deserialize_fixture(const char *json_str) {
    Fixture *fixture = malloc(sizeof(Fixture));
    if (!fixture) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *fixture_id_obj, *fixture_name_obj, *fixture_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(fixture);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "fixture_id", &fixture_id_obj);
    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj);
    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj);

    strncpy(fixture->fixture_id, json_object_get_string(fixture_id_obj), sizeof(fixture->fixture_id) - 1);
    strncpy(fixture->fixture_name, json_object_get_string(fixture_name_obj), sizeof(fixture->fixture_name) - 1);
    strncpy(fixture->fixture_data, json_object_get_string(fixture_data_obj), sizeof(fixture->fixture_data) - 1);

    json_object_put(parsed_json);
    return fixture;
}

void process_fixture_data(const char *json_str) {
    if (!validate_fixture_json(json_str)) {
        printf("Invalid fixture data format\n");
        return;
    }

    Fixture *fixture = deserialize_fixture(json_str);
    if (!fixture) {
        printf("Failed to deserialize fixture data\n");
        return;
    }

    printf("Fixture ID: %s, Fixture Name: %s, Fixture Data: %s\n", fixture->fixture_id, fixture->fixture_name, fixture->fixture_data);
    free(fixture);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter fixture data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_fixture_data(buffer);

    return 0;
}