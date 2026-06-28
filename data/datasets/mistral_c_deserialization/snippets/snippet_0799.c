#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *fixture_name;
    char *description;
} TestFixture;

void load_fixture(TestFixture *fixture) {
    printf("Loading fixture: %s\n", fixture->fixture_name);
    printf("Description: %s\n", fixture->description);
}

int main() {
    const char *external_fixture = "{\"fixture_name\":\"user_auth\",\"description\":\"Tests user authentication\"}";
    struct json_object *parsed_json;
    struct json_object *fixture_name;
    struct json_object *description;
    TestFixture fixture;

    parsed_json = json_tokener_parse(external_fixture);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name);
    json_object_object_get_ex(parsed_json, "description", &description);

    if (fixture_name == NULL || description == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    fixture.fixture_name = strdup(json_object_get_string(fixture_name));
    fixture.description = strdup(json_object_get_string(description));

    load_fixture(&fixture);

    free(fixture.fixture_name);
    free(fixture.description);
    json_object_put(parsed_json);

    return 0;
}