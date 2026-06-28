#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} Person;

void process_person(Person* person) {
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <base64_encoded_person>\n", argv[0]);
        return 1;
    }

    char* base64_input = argv[1];
    unsigned char* decoded_data = base64_decode(base64_input, strlen(base64_input));
    if (!decoded_data) {
        printf("Failed to decode base64 input.\n");
        return 1;
    }

    Person* person = (Person*)decoded_data;
    process_person(person);

    free(decoded_data);
    return 0;
}