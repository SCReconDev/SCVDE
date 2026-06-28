#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(char* data, Person* person) {
    char* token = strtok(data, ",");
    person->name = strdup(token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

void handle_request(char* payload) {
    Person person;
    char* decoded = base64_decode(payload, strlen(payload));
    deserialize_person(decoded, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(decoded);
    free(person.name);
}

int main() {
    char* payload = "TWF0dCxhZ2U="; // Base64 encoded "Matt,age"
    handle_request(payload);
    return 0;
}