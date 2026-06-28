#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_SECRET_KEY_ENV_VAR "PAYMENT_SECRET_KEY"

char* get_payment_secret_key() {
    char* secret_key = getenv(PAYMENT_SECRET_KEY_ENV_VAR);
    if (secret_key == NULL) {
        fprintf(stderr, "Error: Payment secret key not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return secret_key;
}

void process_payment() {
    char* secret_key = get_payment_secret_key();
    printf("Processing payment with secret key: %s\n", secret_key);
    // Simulate payment processing
}

int main() {
    process_payment();
    return 0;
}