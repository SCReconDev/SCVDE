#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_request(const char* data) {
    Person* person = (Person*)malloc(sizeof(Person));
    char* decoded = base64_decode(data, strlen(data));
    memcpy(person, decoded, sizeof(Person));
    free(decoded);

    printf("Name: %s, Age: %d\n", person->name, person->age);
    free(person);
}

int main() {
    char* request = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMw";
    process_request(request);
    return 0;
}