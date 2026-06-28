#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    int age;
} Person;

void parse_person(json_object *jobj, Person *person) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "name") == 0) {
            person->name = strdup(json_object_get_string(val));
        } else if (strcmp(key, "age") == 0) {
            person->age = json_object_get_int(val);
        }
    }
}

int main() {
    const char *json_str = "{\"name\":\"John Doe\",\"age\":30}";
    json_object *jobj = json_tokener_parse(json_str);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Person person;
    parse_person(jobj, &person);

    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);

    free(person.name);
    json_object_put(jobj);

    return 0;
}