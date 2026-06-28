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

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    struct json_object* parsed_json;
    struct json_object* name;
    struct json_object* age;
    Person person;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "age", &age);

    if (name == NULL || age == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    person.name = strdup(json_object_get_string(name));
    person.age = json_object_get_int(age);

    process_person(&person);

    free(person.name);
    json_object_put(parsed_json);

    return 0;
}