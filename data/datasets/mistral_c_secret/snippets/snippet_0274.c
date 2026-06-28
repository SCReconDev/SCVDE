#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

int process_payment(const char* payment_id) {
    // Simulate processing a payment
    printf("Processing payment %s with secret key: %s\n", payment_id, SECRET_KEY);

    return 0;
}

int main() {
    process_payment("payment_12345");
    return 0;
}