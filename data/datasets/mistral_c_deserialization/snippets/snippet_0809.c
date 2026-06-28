#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *fixture_name;
    char *fixture_data;
} FixtureData;

void deserialize_fixture_data(const char *json_str, FixtureData *fixture_data) {
    struct json_object *parsed_json;
    struct json_object *fixture_name_obj, *fixture_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "fixture_name", &fixture_name_obj);
    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj);

    if (fixture_name_obj != NULL && json_object_get_type(fixture_name_obj) == json_type_string) {
        fixture_data->fixture_name = strdup(json_object_get_string(fixture_name_obj));
    }

    if (fixture_data_obj != NULL && json_object_get_type(fixture_data_obj) == json_type_string) {
        fixture_data->fixture_data = strdup(json_object_get_string(fixture_data_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"fixture_name\":\"test_db\",\"fixture_data\":\"sample_data\"}";
    FixtureData fixture_data;

    deserialize_fixture_data(json_str, &fixture_data);

    printf("Fixture Name: %s\n", fixture_data.fixture_name);
    printf("Fixture Data: %s\n", fixture_data.fixture_data);

    free(fixture_data.fixture_name);
    free(fixture_data.fixture_data);
    return 0;
}