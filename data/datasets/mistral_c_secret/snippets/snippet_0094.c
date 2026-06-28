#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

void process_payment(const char* payment_details) {
    printf("Processing payment: %s\n", payment_details);
    // Simulate payment processing
}

int main() {
    process_payment("payment_details");
    return 0;
}