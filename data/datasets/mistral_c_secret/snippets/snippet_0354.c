#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

void process_payment(const char* card_number, const char* expiry_date, const char* cvv) {
    printf("Processing payment for card: %s\n", card_number);
    printf("Using secret key: %s\n", SECRET_KEY);
    // Simulate payment processing
}

int main() {
    process_payment("4111111111111111", "12/25", "123");
    return 0;
}