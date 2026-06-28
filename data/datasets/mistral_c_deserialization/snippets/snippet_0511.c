#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    int age;
} Person;

void process_person(Person *person) {
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("person.json", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    struct json_object *name_obj, *age_obj;
    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "age", &age_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Person person;
    strncpy(person.name, json_object_get_string(name_obj), sizeof(person.name) - 1);
    person.age = json_object_get_int(age_obj);

    process_person(&person);

    json_object_put(parsed_json);
    return 0;
}