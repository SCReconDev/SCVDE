#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

int process_payment(const char* card_number, double amount) {
    // Simulate processing a payment
    printf("Processing payment of $%.2f for card %s with secret key: %s\n", amount, card_number, SECRET_KEY);

    return 0;
}

int main() {
    process_payment("4111111111111111", 100.00);

    return 0;
}