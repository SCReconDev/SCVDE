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

    if (!json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name)) {
        fprintf(stderr, "Error: 'fixture_name' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data)) {
        fprintf(stderr, "Error: 'fixture_data' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    fixture->fixture_name = strdup(json_object_get_string(fixture_name));
    fixture->fixture_data = strdup(json_object_get_string(fixture_data));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"fixture_name\":\"test_data\",\"fixture_data\":\"sample_input\"}";
    Fixture fixture;

    deserialize_fixture(json_str, &fixture);

    printf("Fixture Name: %s\n", fixture.fixture_name);
    printf("Fixture Data: %s\n", fixture.fixture_data);

    free(fixture.fixture_name);
    free(fixture.fixture_data);
    return 0;
}