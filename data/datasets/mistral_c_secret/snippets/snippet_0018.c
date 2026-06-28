#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

int admin_action(const char* action) {
    // Simulate performing an admin action
    printf("Performing admin action '%s' with private key: %s\n", action, PRIVATE_KEY);

    return 0;
}

int main() {
    admin_action("backup");

    return 0;
}