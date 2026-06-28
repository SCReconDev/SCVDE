#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *fixture_name;
    char *fixture_data;
} TestFixture;

void parse_test_fixture(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *fixture_name;
    struct json_object *fixture_data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name)) {
        fprintf(stderr, "Fixture name not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data)) {
        fprintf(stderr, "Fixture data not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    TestFixture test_fixture;
    test_fixture.fixture_name = strdup(json_object_get_string(fixture_name));
    test_fixture.fixture_data = strdup(json_object_get_string(fixture_data));

    printf("Fixture Name: %s, Fixture Data: %s\n", test_fixture.fixture_name, test_fixture.fixture_data);

    free(test_fixture.fixture_name);
    free(test_fixture.fixture_data);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"fixture_name\":\"test_data\",\"fixture_data\":\"{\\\"value\\\":123}\"}";
    parse_test_fixture(json_str);
    return 0;
}