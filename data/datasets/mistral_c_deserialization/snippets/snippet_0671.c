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
    const char* json_str = "{\"name\":\"John Doe\",\"age\":30}";
    struct json_object* json_obj = json_tokener_parse(json_str);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Person person;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "name") == 0) {
            person.name = strdup(json_object_get_string(val));
        } else if (strcmp(key, "age") == 0) {
            person.age = json_object_get_int(val);
        }
    }

    process_person(&person);
    free(person.name);
    json_object_put(json_obj);

    return 0;
}