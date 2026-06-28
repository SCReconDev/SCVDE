#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

void admin_script() {
    char command[256];
    snprintf(command, sizeof(command), "admin_tool --key %s", PRIVATE_KEY);
    printf("Running admin script: %s\n", command);
    system(command);
}

int main() {
    admin_script();
    return 0;
}