#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_person(Person* person) {
    printf("Name: %s, Age: %d\n", person->name, person->age);
}

int main() {
    char* encoded_data = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMwfQ==";
    char* decoded_data = base64_decode(encoded_data, strlen(encoded_data));
    Person* person = (Person*)malloc(sizeof(Person));
    memcpy(person, decoded_data, sizeof(Person));
    process_person(person);
    free(person);
    free(decoded_data);
    return 0;
}