#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *fixture_name;
    int test_count;
} TestFixture;

void deserialize_test_fixture(const char *json_str, TestFixture *fixture) {
    struct json_object *parsed_json;
    struct json_object *fixture_name;
    struct json_object *test_count;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name)) {
        fixture->fixture_name = strdup(json_object_get_string(fixture_name));
    }

    if (json_object_object_get_ex(parsed_json, "test_count", &test_count)) {
        fixture->test_count = json_object_get_int(test_count);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"fixture_name\":\"network_tests\",\"test_count\":10}";
    TestFixture fixture;

    deserialize_test_fixture(json_str, &fixture);

    printf("Fixture Name: %s\n", fixture.fixture_name);
    printf("Test Count: %d\n", fixture.test_count);

    free(fixture.fixture_name);

    return 0;
}