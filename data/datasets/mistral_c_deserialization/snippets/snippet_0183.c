#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    char* decoded = base64_decode(data, strlen(data));
    char* token = strtok(decoded, "|");
    person->name = strdup(token);
    token = strtok(NULL, "|");
    person->age = atoi(token);
    free(decoded);
}

int main() {
    char* user_input = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOiI0MiJ9";
    Person person;
    deserialize_person(user_input, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
    return 0;
}