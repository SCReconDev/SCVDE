#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(char* data, Person* person) {
    char* token = strtok(data, ",");
    strcpy(person->name, token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

void handle_request(char* payload) {
    char* decoded = base64_decode(payload, strlen(payload));
    Person person;
    deserialize_person(decoded, &person);
    printf("Deserialized person: %s, %d\n", person.name, person.age);
    free(decoded);
}

int main() {
    char payload[] = "QWxpY2UsMjU="; // Base64 encoded "Alice,25"
    handle_request(payload);
    return 0;
}