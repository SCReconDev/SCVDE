#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char fixture_id[256];
    char fixture_name[256];
    char fixture_data[256];
} Fixture;

int validate_fixture(Fixture *fixture) {
    if (strlen(fixture->fixture_id) == 0 || strlen(fixture->fixture_name) == 0 || strlen(fixture->fixture_data) == 0) {
        return 0;
    }
    return 1;
}

Fixture* deserialize_fixture(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *fixture_id_obj, *fixture_name_obj, *fixture_data_obj;
    Fixture *fixture = malloc(sizeof(Fixture));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(fixture);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "fixture_id", &fixture_id_obj);
    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj);
    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj);

    if (fixture_id_obj == NULL || fixture_name_obj == NULL || fixture_data_obj == NULL) {
        json_object_put(parsed_json);
        free(fixture);
        return NULL;
    }

    strncpy(fixture->fixture_id, json_object_get_string(fixture_id_obj), sizeof(fixture->fixture_id) - 1);
    strncpy(fixture->fixture_name, json_object_get_string(fixture_name_obj), sizeof(fixture->fixture_name) - 1);
    strncpy(fixture->fixture_data, json_object_get_string(fixture_data_obj), sizeof(fixture->fixture_data) - 1);

    json_object_put(parsed_json);

    if (!validate_fixture(fixture)) {
        free(fixture);
        return NULL;
    }

    return fixture;
}

void process_fixture(Fixture *fixture) {
    printf("Processing fixture: %s, %s, %s\n", fixture->fixture_id, fixture->fixture_name, fixture->fixture_data);
}

int main() {
    char input[MAX_INPUT_SIZE];
    Fixture *fixture;

    printf("Enter fixture data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    fixture = deserialize_fixture(input);
    if (fixture == NULL) {
        printf("Invalid fixture data\n");
        return 1;
    }

    process_fixture(fixture);

    free(fixture);
    return 0;
}