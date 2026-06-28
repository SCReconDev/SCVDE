#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char name[50];
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    char* decoded_data = base64_decode(data, strlen(data));
    sscanf(decoded_data, "%49s %d", person->name, &person->age);
    free(decoded_data);
}

void handle_request(const char* request_data) {
    Person person;
    deserialize_person(request_data, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
}

int main() {
    const char* request_data = "eyJuYW1lIjogIkpvaG4gRG9lIiwgImFnZSI6IDMwIH0=";
    handle_request(request_data);
    return 0;
}