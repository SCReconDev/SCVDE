#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_person(Person* person) {
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
}

Person* deserialize_person(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* name_obj;
    struct json_object* age_obj;
    Person* person = malloc(sizeof(Person));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(person);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "age", &age_obj);

    if (name_obj == NULL || age_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(person);
        return NULL;
    }

    person->name = strdup(json_object_get_string(name_obj));
    person->age = json_object_get_int(age_obj);

    json_object_put(parsed_json);
    return person;
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    Person* person = deserialize_person(json_str);

    if (person != NULL) {
        process_person(person);
        free(person->name);
        free(person);
    }

    return 0;
}