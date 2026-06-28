#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

int process_payment(const char* payment_data) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.stripe.com/v1/charges?key=%s", SECRET_KEY);

    // Simulate payment processing
    printf("Processing payment with data: %s\n", payment_data);

    return 0;
}

int main() {
    process_payment("payment_data_1");
    process_payment("payment_data_2");

    return 0;
}