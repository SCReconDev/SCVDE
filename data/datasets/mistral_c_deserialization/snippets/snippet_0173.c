#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_request(char* data) {
    Person* person = (Person*)malloc(sizeof(Person));
    memcpy(person, data, sizeof(Person));
    printf("Name: %s, Age: %d\n", person->name, person->age);
    free(person);
}

int main() {
    char buffer[1024];
    read(STDIN_FILENO, buffer, sizeof(buffer));
    process_request(buffer);
    return 0;
}