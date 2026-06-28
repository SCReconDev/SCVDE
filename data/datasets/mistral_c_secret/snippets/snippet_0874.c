#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SECRET_KEY_LENGTH 100

char* get_secret_key() {
    char* secret_key = getenv("PAYMENT_SECRET_KEY");
    if (secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(secret_key);
}

void process_payment(char* secret_key) {
    printf("Processing payment with secret key: %s\n", secret_key);
    // Simulate payment processing
}

int main() {
    char* secret_key = get_secret_key();
    process_payment(secret_key);
    free(secret_key);
    return 0;
}