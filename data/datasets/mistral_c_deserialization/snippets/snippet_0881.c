#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_person(Person* person) {
    printf("Name: %s, Age: %d\n", person->name, person->age);
}

int main() {
    const char* json_payload = "{\"name\":\"John Doe\",\"age\":30}";
    struct json_object* parsed_json;
    struct json_object* name_obj;
    struct json_object* age_obj;
    Person person;

    parsed_json = json_tokener_parse(json_payload);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "age", &age_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    person.name = strdup(json_object_get_string(name_obj));
    person.age = json_object_get_int(age_obj);

    process_person(&person);

    free(person.name);
    json_object_put(parsed_json);

    return 0;
}