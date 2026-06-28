#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char name[50];
    int age;
} Person;

void process_data(char* data) {
    Person* person = (Person*)malloc(sizeof(Person));
    memcpy(person, data, sizeof(Person));
    printf("Name: %s, Age: %d\n", person->name, person->age);
    free(person);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <base64_encoded_data>\n", argv[0]);
        return 1;
    }

    char* encoded_data = argv[1];
    char* decoded_data = base64_decode(encoded_data, strlen(encoded_data));

    process_data(decoded_data);

    free(decoded_data);
    return 0;
}