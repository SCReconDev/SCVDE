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

void handle_request(char* encoded_data) {
    char* decoded_data = base64_decode(encoded_data, strlen(encoded_data));
    Person person;
    deserialize_person(decoded_data, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(decoded_data);
    free(person.name);
}

int main() {
    char* encoded_data = "eyJuYW1lIjogIkpvaG4gRG9lIiwgImFnZSI6IDMwIH0=";
    handle_request(encoded_data);
    return 0;
}