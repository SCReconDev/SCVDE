#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* fixture_name;
    char* data;
} Fixture;

void load_fixture(const char* external_fixture) {
    cJSON* json = cJSON_Parse(external_fixture);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* fixture_name = cJSON_GetObjectItemCaseSensitive(json, "fixture_name");
    cJSON* data = cJSON_GetObjectItemCaseSensitive(json, "data");

    if (cJSON_IsString(fixture_name) && (fixture_name->valuestring != NULL) && cJSON_IsString(data) && (data->valuestring != NULL)) {
        Fixture fixture;
        fixture.fixture_name = strdup(fixture_name->valuestring);
        fixture.data = strdup(data->valuestring);

        printf("Fixture: %s, Data: %s\n", fixture.fixture_name, fixture.data);

        free(fixture.fixture_name);
        free(fixture.data);
    }

    cJSON_Delete(json);
}

int main() {
    const char* external_fixture = "{\"fixture_name\":\"test_data\",\"data\":\"sample\"}";
    load_fixture(external_fixture);
    return 0;
}