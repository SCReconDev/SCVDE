#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_name;
    char* fixture_value;
} Fixture;

bool validate_fixture_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_fixture_name = json_object_object_get_ex(obj, "fixture_name", NULL);
    bool has_fixture_value = json_object_object_get_ex(obj, "fixture_value", NULL);

    json_object_put(obj);
    return has_fixture_name && has_fixture_value;
}

Fixture* deserialize_fixture(const char* json_str) {
    if (!validate_fixture_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    Fixture* fixture = malloc(sizeof(Fixture));

    struct json_object* fixture_name_obj;
    json_object_object_get_ex(obj, "fixture_name", &fixture_name_obj);
    fixture->fixture_name = strdup(json_object_get_string(fixture_name_obj));

    struct json_object* fixture_value_obj;
    json_object_object_get_ex(obj, "fixture_value", &fixture_value_obj);
    fixture->fixture_value = strdup(json_object_get_string(fixture_value_obj));

    json_object_put(obj);
    return fixture;
}

void free_fixture(Fixture* fixture) {
    free(fixture->fixture_name);
    free(fixture->fixture_value);
    free(fixture);
}

void load_fixture(const char* json_str) {
    Fixture* fixture = deserialize_fixture(json_str);
    if (fixture == NULL) {
        printf("Invalid fixture data\n");
        return;
    }

    printf("Fixture Name: %s, Fixture Value: %s\n", fixture->fixture_name, fixture->fixture_value);
    free_fixture(fixture);
}

int main() {
    const char* json_str = "{\"fixture_name\":\"test_data\",\"fixture_value\":\"sample_data\"}";
    load_fixture(json_str);
    return 0;
}