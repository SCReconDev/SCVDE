#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *gateway_url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *gateway_url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->gateway_url = strdup(gateway_url);
    config->secret_key = strdup(SECRET_KEY);

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->gateway_url);
        free(config->secret_key);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *transaction_id) {
    if (config == NULL || transaction_id == NULL) {
        return -1;
    }

    printf("Processing payment for transaction %s with secret key %s\n", transaction_id, config->secret_key);
    return 0;
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("https://gateway.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    process_payment(config, "txn_1234567890");

    destroy_payment_gateway_config(config);
    return 0;
}