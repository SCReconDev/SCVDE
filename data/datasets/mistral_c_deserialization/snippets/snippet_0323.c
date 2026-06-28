#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    sscanf(data, "%49[^|]|%d", person->name, &person->age);
}

int main() {
    char input[100];
    Person person;

    printf("Enter person data (name|age): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    deserialize_person(input, &person);

    printf("Name: %s\nAge: %d\n", person.name, person.age);

    return 0;
}