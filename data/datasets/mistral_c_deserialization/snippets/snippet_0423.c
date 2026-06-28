#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(Person *person, const char *data) {
    char *token = strtok((char *)data, ",");
    strcpy(person->name, token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

void handle_request(const char *payload) {
    Person person;
    char decoded_payload[100];
    base64_decode(decoded_payload, payload, strlen(payload));
    deserialize_person(&person, decoded_payload);
    printf("Deserialized: Name=%s, Age=%d\n", person.name, person.age);
}

int main() {
    const char *payload = "TWF0dCxhZ2U="; // Base64 encoded "Matt,age"
    handle_request(payload);
    return 0;
}