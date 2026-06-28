#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* fixture_id;
    char* description;
    int test_count;
    char** tests;
} TestFixture;

bool validate_test_fixture_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "fixture_id") ||
        !cJSON_HasObjectItem(json, "description") ||
        !cJSON_HasObjectItem(json, "tests")) {
        return false;
    }

    cJSON* fixture_id = cJSON_GetObjectItemCaseSensitive(json, "fixture_id");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");
    cJSON* tests = cJSON_GetObjectItemCaseSensitive(json, "tests");

    if (!cJSON_IsString(fixture_id) || !cJSON_IsString(description) || !cJSON_IsArray(tests)) {
        return false;
    }

    return true;
}

TestFixture* deserialize_test_fixture(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_test_fixture_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    TestFixture* fixture = (TestFixture*)malloc(sizeof(TestFixture));
    if (!fixture) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* fixture_id = cJSON_GetObjectItemCaseSensitive(json, "fixture_id");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");
    cJSON* tests = cJSON_GetObjectItemCaseSensitive(json, "tests");

    fixture->fixture_id = strdup(fixture_id->valuestring);
    fixture->description = strdup(description->valuestring);
    fixture->test_count = cJSON_GetArraySize(tests);
    fixture->tests = (char**)malloc(fixture->test_count * sizeof(char*));

    for (int i = 0; i < fixture->test_count; i++) {
        cJSON* test = cJSON_GetArrayItem(tests, i);
        if (cJSON_IsString(test)) {
            fixture->tests[i] = strdup(test->valuestring);
        } else {
            fixture->tests[i] = NULL;
        }
    }

    cJSON_Delete(json);

    return fixture;
}

void free_test_fixture(TestFixture* fixture) {
    if (fixture) {
        free(fixture->fixture_id);
        free(fixture->description);
        for (int i = 0; i < fixture->test_count; i++) {
            free(fixture->tests[i]);
        }
        free(fixture->tests);
        free(fixture);
    }
}

int main() {
    const char* json_str = "{\"fixture_id\":\"fixture123\",\"description\":\"Test fixture\",\"tests\":[\"test1\",\"test2\"]}";
    TestFixture* fixture = deserialize_test_fixture(json_str);

    if (fixture) {
        printf("Fixture ID: %s\n", fixture->fixture_id);
        printf("Description: %s\n", fixture->description);
        printf("Tests:\n");
        for (int i = 0; i < fixture->test_count; i++) {
            printf("  %s\n", fixture->tests[i]);
        }
        free_test_fixture(fixture);
    } else {
        printf("Failed to deserialize test fixture.\n");
    }

    return 0;
}