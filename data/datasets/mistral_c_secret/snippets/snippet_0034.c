#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

void process_payment(const char* card_number, const char* cvv) {
    printf("Processing payment for card: %s\n", card_number);
    printf("Using secret key: %s\n", SECRET_KEY);
}

int main() {
    process_payment("1234-5678-9012-3456", "123");
    return 0;
}