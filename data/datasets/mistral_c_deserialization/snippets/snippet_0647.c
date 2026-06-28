#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* test_name;
    char* status;
    int duration;
} Test;

void show_test(Test* test) {
    printf("Test Name: %s\n", test->test_name);
    printf("Status: %s\n", test->status);
    printf("Duration: %d\n", test->duration);
}

int main() {
    const char* json_str = "{\"test_name\":\"Unit Test\",\"status\":\"Passed\",\"duration\":10}";
    struct json_object* parsed_json;
    struct json_object* test_name;
    struct json_object* status;
    struct json_object* duration;
    Test test;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "test_name", &test_name);
    json_object_object_get_ex(parsed_json, "status", &status);
    json_object_object_get_ex(parsed_json, "duration", &duration);

    if (test_name == NULL || status == NULL || duration == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    test.test_name = strdup(json_object_get_string(test_name));
    test.status = strdup(json_object_get_string(status));
    test.duration = json_object_get_int(duration);

    show_test(&test);

    free(test.test_name);
    free(test.status);
    json_object_put(parsed_json);

    return 0;
}