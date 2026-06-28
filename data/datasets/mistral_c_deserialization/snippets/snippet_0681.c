#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    int age;
} Person;

int validate_person(json_object *jobj) {
    json_object *jname, *jage;

    if (!json_object_object_get_ex(jobj, "name", &jname) ||
        !json_object_object_get_ex(jobj, "age", &jage)) {
        return 0;
    }

    if (json_object_get_type(jname) != json_type_string ||
        json_object_get_type(jage) != json_type_int) {
        return 0;
    }

    return 1;
}

Person* deserialize_person(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_person(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Person *person = (Person*)malloc(sizeof(Person));
    if (person == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(person->name, json_object_get_string(json_object_object_get(jobj, "name")));
    person->age = json_object_get_int(json_object_object_get(jobj, "age"));

    json_object_put(jobj);
    return person;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Person *person = deserialize_person(buffer);
    if (person != NULL) {
        printf("Name: %s\nAge: %d\n", person->name, person->age);
        free(person);
    } else {
        printf("Invalid JSON or person data.\n");
    }

    return 0;
}