#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

void admin_script() {
    printf("Running admin script\n");
    printf("Using private key: %s\n", PRIVATE_KEY);
}

int main() {
    admin_script();
    return 0;
}