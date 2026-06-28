#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    char* token = strtok((char*)data, ",");
    person->name = strdup(token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

void handle_request(const char* payload) {
    Person person;
    deserialize_person(payload, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
}

int main() {
    const char* payload = "John Doe,30";
    handle_request(payload);
    return 0;
}