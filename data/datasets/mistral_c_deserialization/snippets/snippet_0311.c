#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(char* data, Person* person) {
    char* token = strtok(data, ",");
    person->name = strdup(token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

void load_fixture(char* fixture) {
    Person person;
    deserialize_person(fixture, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
}

int main() {
    char* fixture = "John Doe,30";
    load_fixture(fixture);
    return 0;
}