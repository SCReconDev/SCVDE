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

char* base64_decode(const char* input) {
    BIO *bio, *b64;
    char *buffer = (char*)malloc(strlen(input));
    memset(buffer, 0, strlen(input));

    bio = BIO_new_mem_buf(input, -1);
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_read(bio, buffer, strlen(input));
    BIO_free_all(bio);

    return buffer;
}

void process_data(const char* data) {
    Person* person = (Person*)data;
    printf("Name: %s, Age: %d\n", person->name, person->age);
}

int main() {
    const char* encoded_data = "eyJuYW1lIjoiSm9obiBEb2UiLCJhZ2UiOjMwfQ==";
    char* decoded_data = base64_decode(encoded_data);
    process_data(decoded_data);
    free(decoded_data);
    return 0;
}