#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *test_name;
    int test_id;
    char *status;
} Test;

void deserialize_test(const char *json_str, Test *test) {
    struct json_object *parsed_json;
    struct json_object *name_obj;
    struct json_object *id_obj;
    struct json_object *status_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "test_name", &name_obj)) {
        test->test_name = strdup(json_object_get_string(name_obj));
    }

    if (json_object_object_get_ex(parsed_json, "test_id", &id_obj)) {
        test->test_id = json_object_get_int(id_obj);
    }

    if (json_object_object_get_ex(parsed_json, "status", &status_obj)) {
        test->status = strdup(json_object_get_string(status_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"test_name\":\"Unit Test\",\"test_id\":1,\"status\":\"passed\"}";
    Test test;

    deserialize_test(json_str, &test);

    printf("Test Name: %s\n", test.test_name);
    printf("Test ID: %d\n", test.test_id);
    printf("Status: %s\n", test.status);

    free(test.test_name);
    free(test.status);
    return 0;
}