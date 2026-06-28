#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

void process_payment() {
    char payment_url[256];
    snprintf(payment_url, sizeof(payment_url), "https://api.stripe.com/v1/charges?key=%s", SECRET_KEY);
    // Simulate processing payment
    printf("Processing payment using: %s\n", payment_url);
}

int main() {
    process_payment();
    return 0;
}