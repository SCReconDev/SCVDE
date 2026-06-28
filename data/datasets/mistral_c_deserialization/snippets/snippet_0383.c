#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
} Person;

void process_request(const char* payload) {
    Person* person = (Person*)malloc(sizeof(Person));
    memcpy(person, payload, sizeof(Person));
    printf("Name: %s, Age: %d\n", person->name, person->age);
    free(person);
}

int main() {
    char payload[100];
    printf("Enter payload: ");
    fgets(payload, sizeof(payload), stdin);
    process_request(payload);
    return 0;
}