#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *merchant_id;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *merchant_id) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    config->merchant_id = strdup(merchant_id);
    config->secret_key = strdup(SECRET_KEY);
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    free(config->merchant_id);
    free(config->secret_key);
    free(config);
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("merchant_123");
    printf("Payment Gateway Config created with secret key: %s\n", config->secret_key);
    destroy_payment_gateway_config(config);
    return 0;
}