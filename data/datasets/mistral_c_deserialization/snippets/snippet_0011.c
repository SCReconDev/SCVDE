#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

typedef struct {
    char* name;
    int age;
} Person;

void deserialize_person(Person* person, const char* data) {
    char* token = strtok((char*)data, ",");
    person->name = strdup(token);
    token = strtok(NULL, ",");
    person->age = atoi(token);
}

char* base64_decode(const char* input) {
    BIO *bio, *b64;
    int decodeLen = strlen(input);
    char* buffer = (char*)malloc(decodeLen);

    bio = BIO_new_mem_buf(input, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    decodeLen = BIO_read(bio, buffer, strlen(input));
    buffer[decodeLen] = '\0';

    BIO_free_all(bio);
    return buffer;
}

void handle_request(const char* payload) {
    char* decoded = base64_decode(payload);
    Person person;
    deserialize_person(&person, decoded);
    printf("Name: %s, Age: %d\n", person.name, person.age);
    free(decoded);
    free(person.name);
}

int main() {
    const char* payload = "TWFydGluLC0x";
    handle_request(payload);
    return 0;
}