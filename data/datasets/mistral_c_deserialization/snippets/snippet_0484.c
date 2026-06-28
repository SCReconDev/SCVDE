#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} User;

void process_user_data(char* encoded_data) {
    char* decoded_data = base64_decode(encoded_data, strlen(encoded_data));
    User* user = (User*)malloc(sizeof(User));
    memcpy(user, decoded_data, sizeof(User));
    free(decoded_data);
    printf("User: %s, Age: %d\n", user->name, user->age);
    free(user);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <base64_encoded_data>\n", argv[0]);
        return 1;
    }
    process_user_data(argv[1]);
    return 0;
}