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

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "age", &age);

    if (name != NULL && age != NULL) {
        person->name = strdup(json_object_get_string(name));
        person->age = json_object_get_int(age);
    } else {
        fprintf(stderr, "Invalid JSON format\n");
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    Person person;

    deserialize_person(json_str, &person);

    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);

    free(person.name);

    return 0;
}