#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} FixtureData;

void deserialize_fixture_data(const char* json_str, FixtureData* fixture_data) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* fixture_name = cJSON_GetObjectItemCaseSensitive(json, "fixture_name");
    if (cJSON_IsString(fixture_name) && (fixture_name->valuestring != NULL)) {
        fixture_data->fixture_name = strdup(fixture_name->valuestring);
    }

    cJSON* fixture_data_json = cJSON_GetObjectItemCaseSensitive(json, "fixture_data");
    if (cJSON_IsString(fixture_data_json) && (fixture_data_json->valuestring != NULL)) {
        fixture_data->fixture_data = strdup(fixture_data_json->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"fixture_name\":\"example_fixture\",\"fixture_data\":\"Fixture data for example fixture.\"}";
    FixtureData fixture_data;

    deserialize_fixture_data(json_str, &fixture_data);

    printf("Fixture Name: %s\n", fixture_data.fixture_name);
    printf("Fixture Data: %s\n", fixture_data.fixture_data);

    free(fixture_data.fixture_name);
    free(fixture_data.fixture_data);

    return 0;
}