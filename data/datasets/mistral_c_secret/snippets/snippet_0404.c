#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

void process_payment(float amount) {
    char payment_url[256];
    snprintf(payment_url, sizeof(payment_url), "https://api.stripe.com/v1/charges?amount=%d&key=%s", (int)(amount * 100), SECRET_KEY);
    printf("Processing payment via: %s\n", payment_url);
}

int main() {
    process_payment(99.99);
    return 0;
}