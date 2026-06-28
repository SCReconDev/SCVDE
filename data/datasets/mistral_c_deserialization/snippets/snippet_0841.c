#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char name[50];
    int age;
} Person;

void process_person_data(const char *json_data) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *age_obj;
    Person person;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "age", &age_obj)) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(person.name, json_object_get_string(name_obj), sizeof(person.name) - 1);
    person.age = json_object_get_int(age_obj);

    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);

    json_object_put(parsed_json);
}

int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter JSON data: ");
    fgets(input, sizeof(input), stdin);

    process_person_data(input);

    return 0;
}