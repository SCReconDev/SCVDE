#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* name;
    int age;
} Person;

void handle_request(const char* payload) {
    cJSON* json = cJSON_Parse(payload);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");

    if (cJSON_IsString(name) && (name->valuestring != NULL) && cJSON_IsNumber(age)) {
        Person person;
        person.name = strdup(name->valuestring);
        person.age = age->valueint;

        printf("Person: %s, Age: %d\n", person.name, person.age);

        free(person.name);
    }

    cJSON_Delete(json);
}

int main() {
    const char* payload = "{\"name\":\"John Doe\",\"age\":30}";
    handle_request(payload);
    return 0;
}