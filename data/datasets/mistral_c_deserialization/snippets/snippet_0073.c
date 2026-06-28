#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(Person *person, const char *data) {
    sscanf(data, "%49s %d", person->name, &person->age);
}

void handle_request(const char *payload) {
    Person person;
    deserialize_person(&person, payload);
    printf("Deserialized person: %s, %d\n", person.name, person.age);
}

int main() {
    char payload[100];
    printf("Enter person data: ");
    fgets(payload, sizeof(payload), stdin);
    handle_request(payload);
    return 0;
}