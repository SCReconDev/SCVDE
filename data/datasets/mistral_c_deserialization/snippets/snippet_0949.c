#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} Fixture;

void parse_fixture_data(const char* data) {
    cJSON* json = cJSON_Parse(data);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* fixture_name = cJSON_GetObjectItemCaseSensitive(json, "fixture_name");
    cJSON* fixture_data = cJSON_GetObjectItemCaseSensitive(json, "fixture_data");

    if (cJSON_IsString(fixture_name) && (fixture_name->valuestring != NULL)) {
        printf("Fixture Name: %s\n", fixture_name->valuestring);
    }

    if (cJSON_IsString(fixture_data) && (fixture_data->valuestring != NULL)) {
        printf("Fixture Data: %s\n", fixture_data->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* data = "{\"fixture_name\":\"example_fixture\",\"fixture_data\":\"{\\\"param1\\\":\\\"value1\\\"}\"}";
    parse_fixture_data(data);
    return 0;
}