#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* name;
    int age;
} Person;

void parse_json(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* name;
    struct json_object* age;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "name", &name)) {
        Person* person = (Person*)malloc(sizeof(Person));
        person->name = strdup(json_object_get_string(name));

        if (json_object_object_get_ex(parsed_json, "age", &age)) {
            person->age = json_object_get_int(age);
        } else {
            person->age = 0;
        }

        printf("Name: %s, Age: %d\n", person->name, person->age);
        free(person->name);
        free(person);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    parse_json(json_str);
    return 0;
}