#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN RSA PRIVATE KEY-----\nMIIEpAIBAAKCAQEA1Q2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1ZQ2wRw5XJQ1Z\n-----END RSA PRIVATE KEY-----"

void admin_action() {
    char admin_command[256];
    snprintf(admin_command, sizeof(admin_command), "admin_action --key %s", PRIVATE_KEY);
    // Simulate performing admin action
    printf("Performing admin action using command: %s\n", admin_command);
}

int main() {
    admin_action();
    return 0;
}