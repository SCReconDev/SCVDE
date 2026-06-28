#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

typedef struct {
    char* name;
    int age;
} User;

void process_user_data(const char* encoded_data) {
    char* decoded_data = base64_decode(encoded_data, strlen(encoded_data));
    User* user = (User*)decoded_data;
    printf("User name: %s, Age: %d\n", user->name, user->age);
    free(decoded_data);
}

int main() {
    const char* user_data = "eyJuYW1lIjoiQWxpY2UiLCJhZ2UiOjMw";
    process_user_data(user_data);
    return 0;
}