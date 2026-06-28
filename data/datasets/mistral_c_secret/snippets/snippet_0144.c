#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

void process_payment(float amount) {
    char payment_url[256];
    snprintf(payment_url, sizeof(payment_url), "https://payment.example.com/process?amount=%.2f&key=%s", amount, SECRET_KEY);
    printf("Processing payment via: %s\n", payment_url);
}

int main() {
    process_payment(100.50);
    process_payment(200.75);
    return 0;
}