#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(Person* person, const char* data) {
    char* decoded = base64_decode(data, strlen(data));
    sscanf(decoded, "%[^|]|%d", person->name, &person->age);
    free(decoded);
}

int main() {
    char* user_data = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMwfQ==";
    Person person;
    deserialize_person(&person, user_data);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    return 0;
}