#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void parse_fixture(const char* fixture) {
    struct json_object* parsed_json;
    struct json_object* fixture_name;
    struct json_object* fixture_data;

    parsed_json = json_tokener_parse(fixture);

    if (json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name)) {
        TestFixture* test_fixture = (TestFixture*)malloc(sizeof(TestFixture));
        test_fixture->fixture_name = strdup(json_object_get_string(fixture_name));

        if (json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data)) {
            test_fixture->fixture_data = strdup(json_object_get_string(fixture_data));
        } else {
            test_fixture->fixture_data = strdup("");
        }

        printf("Fixture Name: %s, Fixture Data: %s\n", test_fixture->fixture_name, test_fixture->fixture_data);
        free(test_fixture->fixture_name);
        free(test_fixture->fixture_data);
        free(test_fixture);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* fixture = "{\"fixture_name\":\"example_fixture\",\"fixture_data\":\"Test data\"}";
    parse_fixture(fixture);
    return 0;
}