#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *fixture_name;
    int fixture_id;
    char *fixture_type;
} Fixture;

void deserialize_fixture(const char *json_str, Fixture *fixture) {
    struct json_object *parsed_json;
    struct json_object *name_obj;
    struct json_object *id_obj;
    struct json_object *type_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "fixture_name", &name_obj)) {
        fixture->fixture_name = strdup(json_object_get_string(name_obj));
    }

    if (json_object_object_get_ex(parsed_json, "fixture_id", &id_obj)) {
        fixture->fixture_id = json_object_get_int(id_obj);
    }

    if (json_object_object_get_ex(parsed_json, "fixture_type", &type_obj)) {
        fixture->fixture_type = strdup(json_object_get_string(type_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"fixture_name\":\"Test Fixture\",\"fixture_id\":1,\"fixture_type\":\"unit\"}";
    Fixture fixture;

    deserialize_fixture(json_str, &fixture);

    printf("Fixture Name: %s\n", fixture.fixture_name);
    printf("Fixture ID: %d\n", fixture.fixture_id);
    printf("Fixture Type: %s\n", fixture.fixture_type);

    free(fixture.fixture_name);
    free(fixture.fixture_type);
    return 0;
}