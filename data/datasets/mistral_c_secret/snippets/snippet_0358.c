#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

void admin_function(const char* action) {
    printf("Performing admin action: %s\n", action);
    printf("Using private key: %s\n", PRIVATE_KEY);
    // Simulate admin action
}

int main() {
    admin_function("backup");
    admin_function("restore");
    return 0;
}