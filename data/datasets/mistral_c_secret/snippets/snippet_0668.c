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
    return strdup(key);
}

void run_admin_script(const char* key) {
    printf("Running admin script with key: %s\n", key);
}

int main() {
    char* key = get_private_key();
    run_admin_script(key);
    free(key);
    return 0;
}