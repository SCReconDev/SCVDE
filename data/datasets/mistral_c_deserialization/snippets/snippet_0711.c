#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* name;
    int age;
    char* address;
} Person;

void deserialize_person(const char* json_str, Person* person) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        person->name = strdup(name->valuestring);
    }

    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");
    if (cJSON_IsNumber(age)) {
        person->age = age->valueint;
    }

    cJSON* address = cJSON_GetObjectItemCaseSensitive(json, "address");
    if (cJSON_IsString(address) && (address->valuestring != NULL)) {
        person->address = strdup(address->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30,\"address\":\"123 Main St\"}";
    Person person;

    deserialize_person(json_str, &person);

    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);
    printf("Address: %s\n", person.address);

    free(person.name);
    free(person.address);

    return 0;
}