#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[MAX_BUFFER_SIZE];
    int age;
} Person;

void process_person_data(const char* json_data) {
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
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(person.name, json_object_get_string(name_obj), MAX_BUFFER_SIZE - 1);
    person.age = json_object_get_int(age_obj);

    printf("Name: %s, Age: %d\n", person.name, person.age);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"name\":\"John Doe\",\"age\":30}";
    process_person_data(json_data);
    return 0;
}