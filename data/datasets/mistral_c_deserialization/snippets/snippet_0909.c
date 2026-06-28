#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* fixture_name;
    int fixture_id;
} TestFixture;

void load_fixture(TestFixture* fixture) {
    printf("Loading test fixture: %s with ID: %d\n", fixture->fixture_name, fixture->fixture_id);
}

int main() {
    const char* external_fixture = "{\"fixture_name\":\"auth\",\"fixture_id\":456}";
    cJSON* json = cJSON_Parse(external_fixture);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    TestFixture fixture;
    cJSON* fixture_name = cJSON_GetObjectItemCaseSensitive(json, "fixture_name");
    if (cJSON_IsString(fixture_name) && (fixture_name->valuestring != NULL)) {
        fixture.fixture_name = strdup(fixture_name->valuestring);
    } else {
        fprintf(stderr, "Invalid fixture name in external fixture\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* fixture_id = cJSON_GetObjectItemCaseSensitive(json, "fixture_id");
    if (cJSON_IsNumber(fixture_id)) {
        fixture.fixture_id = fixture_id->valueint;
    } else {
        fprintf(stderr, "Invalid fixture ID in external fixture\n");
        free(fixture.fixture_name);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    load_fixture(&fixture);
    free(fixture.fixture_name);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}