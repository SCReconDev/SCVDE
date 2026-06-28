#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *fixture_name;
    int fixture_value;
} Fixture;

void load_fixture(const char *fixture_data, Fixture *fixtures, int *count) {
    struct json_object *parsed_json;
    struct json_object *fixtures_array;
    size_t i;

    parsed_json = json_tokener_parse(fixture_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "fixtures", &fixtures_array)) {
        *count = json_object_array_length(fixtures_array);
        for (i = 0; i < *count; i++) {
            struct json_object *fixture_obj = json_object_array_get_idx(fixtures_array, i);
            struct json_object *name_obj;
            struct json_object *value_obj;

            if (json_object_object_get_ex(fixture_obj, "name", &name_obj)) {
                fixtures[i].fixture_name = strdup(json_object_get_string(name_obj));
            }

            if (json_object_object_get_ex(fixture_obj, "value", &value_obj)) {
                fixtures[i].fixture_value = json_object_get_int(value_obj);
            }
        }
    }

    json_object_put(parsed_json);
}

int main() {
    const char *fixture_data = "{\"fixtures\":[{\"name\":\"fixture1\",\"value\":1},{\"name\":\"fixture2\",\"value\":2}]}";
    Fixture fixtures[10];
    int count = 0;
    int i;

    load_fixture(fixture_data, fixtures, &count);

    for (i = 0; i < count; i++) {
        printf("Fixture Name: %s, Fixture Value: %d\n", fixtures[i].fixture_name, fixtures[i].fixture_value);
        free(fixtures[i].fixture_name);
    }

    return 0;
}