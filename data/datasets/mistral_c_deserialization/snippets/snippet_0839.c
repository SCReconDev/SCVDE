#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    int version;
} TestFixture;

void deserialize_test_fixture(const char* json_str, TestFixture* fixture) {
    struct json_object* parsed_json;
    struct json_object* fixture_name;
    struct json_object* version;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name);
    json_object_object_get_ex(parsed_json, "version", &version);

    if (fixture_name != NULL && json_object_get_type(fixture_name) == json_type_string) {
        fixture->fixture_name = strdup(json_object_get_string(fixture_name));
    }

    if (version != NULL && json_object_get_type(version) == json_type_int) {
        fixture->version = json_object_get_int(version);
    }

    json_object_put(parsed_json);
}

void load_test_fixture(const char* external_fixture) {
    TestFixture fixture = {NULL, 0};
    deserialize_test_fixture(external_fixture, &fixture);

    if (fixture.fixture_name != NULL) {
        printf("Fixture Name: %s\n", fixture.fixture_name);
        free(fixture.fixture_name);
    }

    printf("Version: %d\n", fixture.version);
}

int main() {
    const char* external_fixture = "{\"fixture_name\":\"test_data\",\"version\":1}";
    load_test_fixture(external_fixture);
    return 0;
}