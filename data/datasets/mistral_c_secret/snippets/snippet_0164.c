#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_XYZ123456789"

int main() {
    char card_number[16] = "4111111111111111";
    char cvv[4] = "123";
    char amount[10] = "100.00";

    char payment_request[256];
    snprintf(payment_request, sizeof(payment_request), "ProcessPayment?card=%s&cvv=%s&amount=%s&key=%s", card_number, cvv, amount, SECRET_KEY);

    printf("Sending payment request: %s\n", payment_request);

    return 0;
}