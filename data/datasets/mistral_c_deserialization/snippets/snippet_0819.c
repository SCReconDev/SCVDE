#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void deserialize_test_fixture(const char* json_str, TestFixture* fixture) {
    struct json_object* parsed_json;
    struct json_object* fixture_name;
    struct json_object* fixture_data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name)) {
        fixture->fixture_name = strdup(json_object_get_string(fixture_name));
    }

    if (json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data)) {
        fixture->fixture_data = strdup(json_object_get_string(fixture_data));
    }

    json_object_put(parsed_json);
}

void process_test_fixture(TestFixture* fixture) {
    printf("Fixture Name: %s\n", fixture->fixture_name);
    printf("Fixture Data: %s\n", fixture->fixture_data);
}

int main() {
    const char* json_str = "{\"fixture_name\":\"user_data\",\"fixture_data\":\"user1, user2, user3\"}";
    TestFixture fixture;

    deserialize_test_fixture(json_str, &fixture);
    process_test_fixture(&fixture);

    free(fixture.fixture_name);
    free(fixture.fixture_data);
    return 0;
}