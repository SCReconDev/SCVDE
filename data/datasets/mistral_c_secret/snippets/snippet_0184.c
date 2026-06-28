#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>

#define SECRET_KEY "fake_secret_key_1234567890"

int process_payment(const char* card_number, const char* expiry_date, const char* cvv) {
    SSL_CTX *ctx;
    SSL *ssl;

    ctx = SSL_CTX_new(TLS_client_method());
    ssl = SSL_new(ctx);

    // Simulate payment processing
    printf("Processing payment for card: %s\n", card_number);

    SSL_free(ssl);
    SSL_CTX_free(ctx);

    return 0;
}

int main() {
    process_payment("4111111111111111", "12/25", "123");

    return 0;
}