#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC7b6J5j6J5j6J5\nj6J5j6J5j6J5j6J5j6J5j6J5j6J5j6J5j6J5j6J5j6J5j6J5j6J5\n-----END PRIVATE KEY-----"

void admin_script() {
    char admin_command[256];
    snprintf(admin_command, sizeof(admin_command), "admin_command --key %s", PRIVATE_KEY);
    printf("Running admin script: %s\n", admin_command);
}

int main() {
    admin_script();
    return 0;
}