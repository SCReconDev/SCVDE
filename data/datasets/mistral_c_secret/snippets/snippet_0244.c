#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

void process_payment(const char* payment_id) {
    printf("Processing payment %s with secret key %s\n", payment_id, SECRET_KEY);
}

int main() {
    process_payment("payment_123");
    process_payment("payment_456");
    return 0;
}