#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

void process_payment(int amount) {
    char payment_url[256];
    snprintf(payment_url, sizeof(payment_url), "https://api.stripe.com/v1/charges?amount=%d&key=%s", amount, SECRET_KEY);
    printf("Processing payment: %s\n", payment_url);
}

int main() {
    process_payment(1000);
    return 0;
}