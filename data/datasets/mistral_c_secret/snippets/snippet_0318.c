#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC7bP\n-----END PRIVATE KEY-----\n"

void admin_function() {
    printf("Admin function using private key: %s\n", PRIVATE_KEY);
}

int main() {
    admin_function();
    return 0;
}