#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    int age;
} Person;

void parse_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *age;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "name", &name)) {
        fprintf(stderr, "Name not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "age", &age)) {
        fprintf(stderr, "Age not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    Person person;
    person.name = strdup(json_object_get_string(name));
    person.age = json_object_get_int(age);

    printf("Name: %s, Age: %d\n", person.name, person.age);

    free(person.name);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"name\":\"John Doe\",\"age\":30}";
    parse_json(json_str);
    return 0;
}