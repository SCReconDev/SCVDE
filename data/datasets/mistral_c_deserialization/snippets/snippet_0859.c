#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char fixture_name[50];
    int fixture_value;
} Fixture;

int deserialize_fixture(const char* json_str, Fixture* fixture) {
    struct json_object *parsed_json;
    struct json_object *fixture_name_obj, *fixture_value_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj)) {
        fprintf(stderr, "Error getting fixture_name\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "fixture_value", &fixture_value_obj)) {
        fprintf(stderr, "Error getting fixture_value\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(fixture->fixture_name, json_object_get_string(fixture_name_obj), sizeof(fixture->fixture_name) - 1);
    fixture->fixture_value = json_object_get_int(fixture_value_obj);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    Fixture fixture;

    printf("Enter fixture JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_fixture(buffer, &fixture) == 0) {
        printf("Deserialized Fixture: Name=%s, Value=%d\n", fixture.fixture_name, fixture.fixture_value);
    } else {
        fprintf(stderr, "Failed to deserialize fixture\n");
    }

    return 0;
}