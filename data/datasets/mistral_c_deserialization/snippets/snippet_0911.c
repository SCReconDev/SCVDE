#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* name;
    int age;
} Person;

bool validate_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_name = json_object_object_get_ex(obj, "name", NULL);
    bool has_age = json_object_object_get_ex(obj, "age", NULL);

    json_object_put(obj);
    return has_name && has_age;
}

Person* deserialize_person(const char* json_str) {
    if (!validate_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    Person* person = malloc(sizeof(Person));

    struct json_object* name_obj;
    json_object_object_get_ex(obj, "name", &name_obj);
    person->name = strdup(json_object_get_string(name_obj));

    struct json_object* age_obj;
    json_object_object_get_ex(obj, "age", &age_obj);
    person->age = json_object_get_int(age_obj);

    json_object_put(obj);
    return person;
}

void free_person(Person* person) {
    free(person->name);
    free(person);
}

void handle_person_data(const char* json_str) {
    Person* person = deserialize_person(json_str);
    if (person == NULL) {
        printf("Invalid person data\n");
        return;
    }

    printf("Name: %s, Age: %d\n", person->name, person->age);
    free_person(person);
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    handle_person_data(json_str);
    return 0;
}