#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

char* get_private_key() {
    char* key = getenv(PRIVATE_KEY_ENV_VAR);
    if (key == NULL) {
        fprintf(stderr, "Error: Private key not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return key;
}

void run_admin_script() {
    char* key = get_private_key();
    printf("Running admin script with private key: %s\n", key);
    // Simulate admin script execution
}

int main() {
    run_admin_script();
    return 0;
}