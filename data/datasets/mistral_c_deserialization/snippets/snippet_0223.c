#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    char* decoded = base64_decode(data, strlen(data));
    sscanf(decoded, "%49[^;];%d", person->name, &person->age);
    free(decoded);
}

int main() {
    char* input = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMwCg==";
    Person person;
    deserialize_person(input, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    return 0;
}