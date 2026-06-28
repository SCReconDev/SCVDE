#include <stdio.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

void admin_function() {
    printf("Executing admin function\n");
    printf("Using private key: %s\n", PRIVATE_KEY);
}

int main() {
    admin_function();
    return 0;
}