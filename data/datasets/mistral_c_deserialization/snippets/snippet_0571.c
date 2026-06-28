#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    int age;
} Person;

bool validate_person_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "name") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "age") == 0 && json_object_get_type(val) != json_type_int) {
            return false;
        }
    }
    return true;
}

Person *deserialize_person(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_person_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Person *person = malloc(sizeof(Person));
    if (!person) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *name_obj, *age_obj;
    if (json_object_object_get_ex(jobj, "name", &name_obj)) {
        person->name = strdup(json_object_get_string(name_obj));
    } else {
        person->name = NULL;
    }

    if (json_object_object_get_ex(jobj, "age", &age_obj)) {
        person->age = json_object_get_int(age_obj);
    } else {
        person->age = 0;
    }

    json_object_put(jobj);
    return person;
}

void free_person(Person *person) {
    if (person) {
        free(person->name);
        free(person);
    }
}

int main() {
    const char *json_str = "{\"name\":\"John Doe\",\"age\":30}";
    Person *person = deserialize_person(json_str);

    if (person) {
        printf("Name: %s\n", person->name);
        printf("Age: %d\n", person->age);
        free_person(person);
    } else {
        printf("Failed to deserialize person.\n");
    }

    return 0;
}