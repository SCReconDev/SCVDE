#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    int age;
} Person;

int deserialize_person(const char* json_str, Person* person) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *age_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "name", &name_obj)) {
        fprintf(stderr, "Error getting name\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "age", &age_obj)) {
        fprintf(stderr, "Error getting age\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(person->name, json_object_get_string(name_obj), sizeof(person->name) - 1);
    person->age = json_object_get_int(age_obj);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    Person person;

    printf("Enter JSON string: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_person(buffer, &person) == 0) {
        printf("Deserialized Person: Name=%s, Age=%d\n", person.name, person.age);
    } else {
        fprintf(stderr, "Failed to deserialize person\n");
    }

    return 0;
}