#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_person(Person* person) {
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
}

int main() {
    const char* json_string = "{\"name\":\"John Doe\",\"age\":30}";
    cJSON* json = cJSON_Parse(json_string);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    Person person;
    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        person.name = strdup(name->valuestring);
    } else {
        fprintf(stderr, "Invalid name in JSON\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");
    if (cJSON_IsNumber(age)) {
        person.age = age->valueint;
    } else {
        fprintf(stderr, "Invalid age in JSON\n");
        free(person.name);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    process_person(&person);
    free(person.name);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}