#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_person(Person* person) {
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
}

void deserialize_person(const char* data, Person* person) {
    char* decoded_data = base64_decode(data, strlen(data));
    sscanf(decoded_data, "%[^|]|%d", person->name, &person->age);
    free(decoded_data);
}

void api_endpoint(const char* payload) {
    Person person;
    deserialize_person(payload, &person);
    process_person(&person);
}

int main() {
    const char* payload = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMwfQ==";
    api_endpoint(payload);
    return 0;
}