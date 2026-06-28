#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    char* token = strtok((char*)data, ",");
    person->name = strdup(token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

int main() {
    FILE* file = fopen("person_data.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);

    Person person;
    deserialize_person(buffer, &person);

    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);

    return 0;
}