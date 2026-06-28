#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* name;
    int age;
} Person;

bool validate_person_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");
    if (!cJSON_IsString(name) || !cJSON_IsNumber(age)) return false;
    return true;
}

Person* deserialize_person(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_person_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Person* person = malloc(sizeof(Person));
    if (!person) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON* age = cJSON_GetObjectItemCaseSensitive(json, "age");

    person->name = strdup(name->valuestring);
    person->age = age->valueint;

    cJSON_Delete(json);
    return person;
}

void free_person(Person* person) {
    if (person) {
        free(person->name);
        free(person);
    }
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    Person* person = deserialize_person(json_str);

    if (person) {
        printf("Name: %s\nAge: %d\n", person->name, person->age);
        free_person(person);
    } else {
        printf("Failed to deserialize person.\n");
    }

    return 0;
}