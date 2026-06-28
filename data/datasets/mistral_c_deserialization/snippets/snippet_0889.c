#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void process_test_fixture(TestFixture* fixture) {
    printf("Fixture Name: %s, Fixture Data: %s\n", fixture->fixture_name, fixture->fixture_data);
}

int main() {
    const char* external_fixture = "{\"fixture_name\":\"user_data\",\"fixture_data\":\"{\\\"users\\\":[{\\\"id\\\":1,\\\"name\\\":\\\"Alice\\\"},{\\\"id\\\":2,\\\"name\\\":\\\"Bob\\\"}]}\"}";
    struct json_object* parsed_json;
    struct json_object* fixture_name_obj;
    struct json_object* fixture_data_obj;
    TestFixture fixture;

    parsed_json = json_tokener_parse(external_fixture);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj) ||
        !json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    fixture.fixture_name = strdup(json_object_get_string(fixture_name_obj));
    fixture.fixture_data = strdup(json_object_get_string(fixture_data_obj));

    process_test_fixture(&fixture);

    free(fixture.fixture_name);
    free(fixture.fixture_data);
    json_object_put(parsed_json);

    return 0;
}