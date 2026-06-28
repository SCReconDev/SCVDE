#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} Person;

void parse_person(Person* person, const char* data) {
    char* token = strtok((char*)data, ",");
    person->name = strdup(token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

int main() {
    char* data = "Jane Smith,25";
    Person person;
    parse_person(&person, data);
    printf("Person: %s, Age: %d\n", person.name, person.age);
    free(person.name);
    return 0;
}