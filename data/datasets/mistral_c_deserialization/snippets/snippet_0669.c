#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char fixture_name[MAX_BUFFER_SIZE];
    char fixture_data[MAX_BUFFER_SIZE];
} TestFixture;

void load_test_fixture(const char *json_str, TestFixture *fixture) {
    struct json_object *parsed_json;
    struct json_object *fixture_name_obj;
    struct json_object *fixture_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj);
    if (fixture_name_obj != NULL) {
        strncpy(fixture->fixture_name, json_object_get_string(fixture_name_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj);
    if (fixture_data_obj != NULL) {
        strncpy(fixture->fixture_data, json_object_get_string(fixture_data_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"fixture_name\":\"database\",\"fixture_data\":\"connection_string=localhost\"}";
    TestFixture fixture;

    load_test_fixture(json_str, &fixture);

    printf("Fixture Name: %s\n", fixture.fixture_name);
    printf("Fixture Data: %s\n", fixture.fixture_data);

    return 0;
}