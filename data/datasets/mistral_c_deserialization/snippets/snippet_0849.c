#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FIXTURE_SIZE 4096

typedef struct {
    char fixture_name[50];
    char fixture_value[100];
} Fixture;

void load_test_fixture(const char *fixture_data) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *value_obj;
    Fixture fixture;

    parsed_json = json_tokener_parse(fixture_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing fixture data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "value", &value_obj)) {
        fprintf(stderr, "Invalid fixture format\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(fixture.fixture_name, json_object_get_string(name_obj), sizeof(fixture.fixture_name) - 1);
    strncpy(fixture.fixture_value, json_object_get_string(value_obj), sizeof(fixture.fixture_value) - 1);

    printf("Fixture Name: %s\n", fixture.fixture_name);
    printf("Fixture Value: %s\n", fixture.fixture_value);

    json_object_put(parsed_json);
}

int main() {
    char fixture[MAX_FIXTURE_SIZE];
    printf("Enter fixture data: ");
    fgets(fixture, sizeof(fixture), stdin);

    load_test_fixture(fixture);

    return 0;
}