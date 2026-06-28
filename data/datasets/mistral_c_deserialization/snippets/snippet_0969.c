#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} Fixture;

void deserialize_fixture(const char* json_str, Fixture* fixture) {
    struct json_object* parsed_json;
    struct json_object* fixture_name;
    struct json_object* fixture_data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name);
    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data);

    if (fixture_name != NULL && json_object_is_type(fixture_name, json_type_string)) {
        fixture->fixture_name = strdup(json_object_get_string(fixture_name));
    }

    if (fixture_data != NULL && json_object_is_type(fixture_data, json_type_string)) {
        fixture->fixture_data = strdup(json_object_get_string(fixture_data));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"fixture_name\":\"test_data\",\"fixture_data\":\"sample_data\"}";
    Fixture fixture;

    deserialize_fixture(json_str, &fixture);

    printf("Fixture Name: %s\n", fixture.fixture_name);
    printf("Fixture Data: %s\n", fixture.fixture_data);

    free(fixture.fixture_name);
    free(fixture.fixture_data);
    return 0;
}