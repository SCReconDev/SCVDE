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
    struct json_object* name_obj;
    struct json_object* age_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "age", &age_obj);

    if (name_obj != NULL && json_object_is_type(name_obj, json_type_string)) {
        person->name = strdup(json_object_get_string(name_obj));
    }

    if (age_obj != NULL && json_object_is_type(age_obj, json_type_int)) {
        person->age = json_object_get_int(age_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    Person person;

    deserialize_person(json_str, &person);

    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);

    free(person.name);
    return 0;
}