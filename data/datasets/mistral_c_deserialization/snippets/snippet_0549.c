#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_id;
    char* data;
} TestFixture;

void load_fixture(const char* json_str, TestFixture* fixture) {
    struct json_object* parsed_json;
    struct json_object* fixture_id;
    struct json_object* data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_id", &fixture_id)) {
        fprintf(stderr, "Error: 'fixture_id' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "data", &data)) {
        fprintf(stderr, "Error: 'data' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    fixture->fixture_id = strdup(json_object_get_string(fixture_id));
    fixture->data = strdup(json_object_get_string(data));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"fixture_id\":\"fixture123\",\"data\":\"test data\"}";
    TestFixture fixture;

    load_fixture(json_str, &fixture);

    printf("Fixture ID: %s\n", fixture.fixture_id);
    printf("Data: %s\n", fixture.data);

    free(fixture.fixture_id);
    free(fixture.data);
    return 0;
}