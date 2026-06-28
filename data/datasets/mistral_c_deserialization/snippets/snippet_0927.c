#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *test_name;
    int test_id;
    char *result;
} Test;

void run_test(Test *test) {
    printf("Test: %s, ID: %d, Result: %s\n", test->test_name, test->test_id, test->result);
}

int main() {
    const char *json_str = "{\"test_name\":\"Unit Test\", \"test_id\":101, \"result\":\"Passed\"}";
    struct json_object *parsed_json;
    struct json_object *test_name_obj, *test_id_obj, *result_obj;
    Test test;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "test_name", &test_name_obj) ||
        !json_object_object_get_ex(parsed_json, "test_id", &test_id_obj) ||
        !json_object_object_get_ex(parsed_json, "result", &result_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    test.test_name = strdup(json_object_get_string(test_name_obj));
    test.test_id = json_object_get_int(test_id_obj);
    test.result = strdup(json_object_get_string(result_obj));

    run_test(&test);

    free(test.test_name);
    free(test.result);
    json_object_put(parsed_json);

    return 0;
}