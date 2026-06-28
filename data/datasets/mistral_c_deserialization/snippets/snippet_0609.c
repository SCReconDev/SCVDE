#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* fixture_id;
    char* fixture_data;
} Fixture;

void process_fixture(Fixture* fixture) {
    printf("Fixture ID: %s\n", fixture->fixture_id);
    printf("Fixture Data: %s\n", fixture->fixture_data);
}

Fixture* deserialize_fixture(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* fixture_id_obj;
    struct json_object* fixture_data_obj;
    Fixture* fixture = malloc(sizeof(Fixture));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(fixture);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "fixture_id", &fixture_id_obj);
    json_object_object_get_ex(parsed_json, "fixture_data", &fixture_data_obj);

    if (fixture_id_obj == NULL || fixture_data_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(fixture);
        return NULL;
    }

    fixture->fixture_id = strdup(json_object_get_string(fixture_id_obj));
    fixture->fixture_data = strdup(json_object_get_string(fixture_data_obj));

    json_object_put(parsed_json);
    return fixture;
}

int main() {
    const char* json_str = "{\"fixture_id\":\"fixture123\",\"fixture_data\":\"test_data\"}";
    Fixture* fixture = deserialize_fixture(json_str);

    if (fixture != NULL) {
        process_fixture(fixture);
        free(fixture->fixture_id);
        free(fixture->fixture_data);
        free(fixture);
    }

    return 0;
}