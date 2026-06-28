#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

void admin_action(const char* action) {
    printf("Performing admin action %s with private key %s\n", action, PRIVATE_KEY);
}

int main() {
    admin_action("backup");
    admin_action("restore");
    return 0;
}