#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char fixture_name[MAX_BUFFER_SIZE];
    char fixture_data[MAX_BUFFER_SIZE];
} Fixture;

void load_test_fixture(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *fixture_name_obj, *fixture_data_obj;
    Fixture fixture;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj) ||
        !json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(fixture.fixture_name, json_object_get_string(fixture_name_obj), MAX_BUFFER_SIZE - 1);
    strncpy(fixture.fixture_data, json_object_get_string(fixture_data_obj), MAX_BUFFER_SIZE - 1);

    printf("Fixture Name: %s, Fixture Data: %s\n", fixture.fixture_name, fixture.fixture_data);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"fixture_name\":\"test_data\",\"fixture_data\":\"test_value\"}";
    load_test_fixture(json_data);
    return 0;
}