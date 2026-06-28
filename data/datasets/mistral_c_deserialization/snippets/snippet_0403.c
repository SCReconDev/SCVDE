#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    char* decoded_data = base64_decode(data, strlen(data));
    sscanf(decoded_data, "%[^:]:%d", person->name, &person->age);
    free(decoded_data);
}

int main() {
    char* user_input = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMwCg==";
    Person person;
    person.name = malloc(100);
    deserialize_person(user_input, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
    return 0;
}