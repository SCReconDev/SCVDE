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

void handle_request(const char* payload) {
    Person person;
    deserialize_person(payload, &person);
    printf("Hello, %s! You are %d years old.\n", person.name, person.age);
    free(person.name);
}

int main() {
    const char* payload = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMwfQ==";
    handle_request(payload);
    return 0;
}