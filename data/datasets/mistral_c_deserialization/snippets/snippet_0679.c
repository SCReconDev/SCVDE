#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} FixtureData;

void load_fixture(FixtureData* fixture) {
    printf("Fixture Name: %s, Fixture Data: %s\n", fixture->fixture_name, fixture->fixture_data);
}

int main() {
    const char* external_fixture = "{\"fixture_name\":\"fixture1\",\"fixture_data\":\"test data\"}";
    struct json_object* json_obj = json_tokener_parse(external_fixture);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    FixtureData fixture;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "fixture_name") == 0) {
            fixture.fixture_name = strdup(json_object_get_string(val));
        } else if (strcmp(key, "fixture_data") == 0) {
            fixture.fixture_data = strdup(json_object_get_string(val));
        }
    }

    load_fixture(&fixture);
    free(fixture.fixture_name);
    free(fixture.fixture_data);
    json_object_put(json_obj);

    return 0;
}