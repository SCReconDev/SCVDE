#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    sscanf(data, "%49s %d", person->name, &person->age);
}

void handle_request(const char* payload) {
    Person person;
    deserialize_person(payload, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
}

int main() {
    char payload[100];
    printf("Enter person data: ");
    fgets(payload, sizeof(payload), stdin);
    handle_request(payload);
    return 0;
}