#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *fixture_id;
    char *data;
} TestFixture;

void parse_test_fixture(json_object *jobj, TestFixture *fixture) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "fixture_id") == 0) {
            fixture->fixture_id = strdup(json_object_get_string(val));
        } else if (strcmp(key, "data") == 0) {
            fixture->data = strdup(json_object_get_string(val));
        }
    }
}

int main() {
    const char *external_fixture = "{\"fixture_id\":\"fix123\",\"data\":\"test data\"}";
    json_object *jobj = json_tokener_parse(external_fixture);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    TestFixture fixture;
    parse_test_fixture(jobj, &fixture);

    printf("Fixture ID: %s\n", fixture.fixture_id);
    printf("Data: %s\n", fixture.data);

    free(fixture.fixture_id);
    free(fixture.data);
    json_object_put(jobj);

    return 0;
}