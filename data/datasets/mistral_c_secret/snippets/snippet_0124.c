#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

void process_payment(float amount) {
    char payment_command[256];
    snprintf(payment_command, sizeof(payment_command), "curl -X POST https://payment.example.com/charge -d 'amount=%f&key=%s'", amount, SECRET_KEY);
    printf("Processing payment: %s\n", payment_command);
    system(payment_command);
}

int main() {
    process_payment(100.00);
    return 0;
}