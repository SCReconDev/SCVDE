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

    if (name != NULL && json_object_get_type(name) == json_type_string) {
        person->name = strdup(json_object_get_string(name));
    }

    if (age != NULL && json_object_get_type(age) == json_type_int) {
        person->age = json_object_get_int(age);
    }

    json_object_put(parsed_json);
}

void handle_api_request(const char* json_payload) {
    Person person = {NULL, 0};
    deserialize_person(json_payload, &person);

    if (person.name != NULL) {
        printf("Name: %s\n", person.name);
        free(person.name);
    }

    printf("Age: %d\n", person.age);
}

int main() {
    const char* json_payload = "{\"name\":\"John Doe\",\"age\":30}";
    handle_api_request(json_payload);
    return 0;
}