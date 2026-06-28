#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void deserialize_test_fixture(const char* json_str, TestFixture* fixture) {
    struct json_object* parsed_json;
    struct json_object* name_obj;
    struct json_object* data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "data", &data_obj);

    if (name_obj != NULL && json_object_is_type(name_obj, json_type_string)) {
        fixture->fixture_name = strdup(json_object_get_string(name_obj));
    }

    if (data_obj != NULL && json_object_is_type(data_obj, json_type_string)) {
        fixture->fixture_data = strdup(json_object_get_string(data_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"name\":\"user_data\",\"data\":\"test_user\"}";
    TestFixture fixture;

    deserialize_test_fixture(json_str, &fixture);

    printf("Fixture Name: %s\n", fixture.fixture_name);
    printf("Fixture Data: %s\n", fixture.fixture_data);

    free(fixture.fixture_name);
    free(fixture.fixture_data);
    return 0;
}