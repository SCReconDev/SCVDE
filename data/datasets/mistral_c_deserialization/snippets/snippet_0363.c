#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char name[256];
    int age;
} Person;

void deserialize_person(Person *person, const char *data) {
    sscanf(data, "%255[^;];%d", person->name, &person->age);
}

void handle_request(const char *data) {
    Person person;
    deserialize_person(&person, data);
    printf("Name: %s, Age: %d\n", person.name, person.age);
}

int main() {
    char buffer[1024];
    printf("Enter person data (name;age): ");
    fgets(buffer, sizeof(buffer), stdin);
    handle_request(buffer);
    return 0;
}