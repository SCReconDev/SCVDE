#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FIXTURE_SIZE 1024

typedef struct {
    char fixture_id[256];
    int fixture_value;
    char fixture_data[256];
} Fixture;

void deserialize_fixture(Fixture *fixture, const char *fixture_data) {
    struct json_object *parsed_json;
    struct json_object *fixture_id_obj, *fixture_value_obj, *fixture_data_obj;

    parsed_json = json_tokener_parse(fixture_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON fixture data\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "fixture_id", &fixture_id_obj);
    json_object_object_get_ex(parsed_json, "fixture_value", &fixture_value_obj);
    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj);

    if (fixture_id_obj != NULL && json_object_is_type(fixture_id_obj, json_type_string)) {
        strncpy(fixture->fixture_id, json_object_get_string(fixture_id_obj), sizeof(fixture->fixture_id) - 1);
    }

    if (fixture_value_obj != NULL && json_object_is_type(fixture_value_obj, json_type_int)) {
        fixture->fixture_value = json_object_get_int(fixture_value_obj);
    }

    if (fixture_data_obj != NULL && json_object_is_type(fixture_data_obj, json_type_string)) {
        strncpy(fixture->fixture_data, json_object_get_string(fixture_data_obj), sizeof(fixture->fixture_data) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    Fixture fixture;
    char fixture_data[MAX_FIXTURE_SIZE];

    printf("Enter fixture data: ");
    fgets(fixture_data, sizeof(fixture_data), stdin);

    deserialize_fixture(&fixture, fixture_data);

    printf("Deserialized Fixture:\n");
    printf("Fixture ID: %s\n", fixture.fixture_id);
    printf("Fixture Value: %d\n", fixture.fixture_value);
    printf("Fixture Data: %s\n", fixture.fixture_data);

    return 0;
}