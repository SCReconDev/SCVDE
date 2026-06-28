#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(const char* data, Person* person) {
    BIO* bio = BIO_new_mem_buf((void*)data, -1);
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    char buffer[1024];
    int len = BIO_read(bio, buffer, sizeof(buffer));
    buffer[len] = '\0';

    char* token = strtok(buffer, ",");
    person->name = strdup(token);

    token = strtok(NULL, ",");
    person->age = atoi(token);

    BIO_free_all(bio);
}

int main() {
    const char* data = "VG9tLDA=";
    Person person;

    deserialize_person(data, &person);

    printf("Name: %s, Age: %d\n", person.name, person.age);

    free(person.name);
    return 0;
}