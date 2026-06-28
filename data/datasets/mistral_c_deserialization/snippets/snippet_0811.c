#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(const char* json_str, Person* person) {
    struct json_object* parsed_json;
    struct json_object* name;
    struct json_object* age;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "name", &name)) {
        person->name = strdup(json_object_get_string(name));
    }

    if (json_object_object_get_ex(parsed_json, "age", &age)) {
        person->age = json_object_get_int(age);
    }

    json_object_put(parsed_json);
}

void process_person(Person* person) {
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    Person person;

    deserialize_person(json_str, &person);
    process_person(&person);

    free(person.name);
    return 0;
}