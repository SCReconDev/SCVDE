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
    char data[100];
    printf("Enter person data (name,age): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = 0;

    Person person;
    deserialize_person(&person, data);

    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
    return 0;
}