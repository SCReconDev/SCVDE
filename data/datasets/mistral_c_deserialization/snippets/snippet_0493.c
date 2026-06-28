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

void handle_request(const char* request_data) {
    Person person;
    deserialize_person(request_data, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
}

int main() {
    const char* request_data = "John Doe,30";
    handle_request(request_data);
    return 0;
}