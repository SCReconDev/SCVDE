#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

int admin_script(const char* command) {
    // Simulate admin command execution
    printf("Executing admin command: %s with private key: %s\n", command, PRIVATE_KEY);

    return 0;
}

int main() {
    admin_script("backup");
    admin_script("restore");

    return 0;
}