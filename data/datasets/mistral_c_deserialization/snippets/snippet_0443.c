#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char name[50];
    int age;
} Person;

void handle_request(const char* payload) {
    Person* person = (Person*)malloc(sizeof(Person));
    memcpy(person, payload, sizeof(Person));
    printf("Name: %s, Age: %d\n", person->name, person->age);
    free(person);
}

int main() {
    char payload[sizeof(Person)];
    memset(payload, 0, sizeof(payload));
    strcpy(payload, "John Doe");
    *(int*)(payload + 50) = 30;

    handle_request(payload);
    return 0;
}