#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void import_preferences(char* user_file) {
    FILE* file = fopen(user_file, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    Person person;
    deserialize_person(buffer, &person);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(person.name);
    fclose(file);
}

int main() {
    char* user_file = "user_preferences.txt";
    import_preferences(user_file);
    return 0;
}