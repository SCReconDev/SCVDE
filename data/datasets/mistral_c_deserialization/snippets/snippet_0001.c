#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(Person *person, const char *data) {
    sscanf(data, "%49s %d", person->name, &person->age);
}

void handle_request(const char *data) {
    Person person;
    deserialize_person(&person, data);
    printf("Name: %s, Age: %d\n", person.name, person.age);
}

int main() {
    char data[100];
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    handle_request(data);
    return 0;
}