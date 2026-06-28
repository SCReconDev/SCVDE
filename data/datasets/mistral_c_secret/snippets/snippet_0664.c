#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY_ENV_VAR "SECRET_KEY"

char* get_secret_key() {
    char* key = getenv(SECRET_KEY_ENV_VAR);
    if (key == NULL) {
        fprintf(stderr, "Error: Secret key not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(key);
}

void process_payment(const char* amount, const char* key) {
    printf("Processing payment of %s with key: %s\n", amount, key);
}

int main() {
    char* key = get_secret_key();
    process_payment("100.00", key);
    free(key);
    return 0;
}