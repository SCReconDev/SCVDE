#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char name[50];
    int age;
} Person;

void process_person(Person *person) {
    printf("Name: %s, Age: %d\n", person->name, person->age);
}

void deserialize_person(const char *data, Person *person) {
    char *decoded = base64_decode(data, strlen(data));
    memcpy(person, decoded, sizeof(Person));
    free(decoded);
}

void api_endpoint(const char *payload) {
    Person person;
    deserialize_person(payload, &person);
    process_person(&person);
}

int main() {
    const char *payload = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMw";
    api_endpoint(payload);
    return 0;
}