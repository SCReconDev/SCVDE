#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(Person* person, const char* data) {
    char* token = strtok((char*)data, ",");
    person->name = strdup(token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

int main() {
    const char* data = "John Doe,30";
    Person person;
    deserialize_person(&person, data);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
    return 0;
}