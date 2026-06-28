#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    int age;
} Person;

int validate_person_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "name") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "age") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Person* deserialize_person(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_person_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Person *person = (Person*)malloc(sizeof(Person));
    if (!person) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jname = json_object_object_get(jobj, "name");
    json_object *jage = json_object_object_get(jobj, "age");

    strcpy(person->name, json_object_get_string(jname));
    person->age = json_object_get_int(jage);

    json_object_put(jobj);
    return person;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Person *person = deserialize_person(buffer);
    if (person) {
        printf("Name: %s, Age: %d\n", person->name, person->age);
        free(person);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}