#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* name;
    int age;
} Person;

void parse_json(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");

    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        printf("Name: %s\n", name->valuestring);
    }

    if (cJSON_IsNumber(age)) {
        printf("Age: %d\n", age->valueint);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    parse_json(json_str);
    return 0;
}