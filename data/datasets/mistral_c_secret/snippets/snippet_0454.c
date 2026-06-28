#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

typedef struct {
    char *merchant_id;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *merchant_id) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->merchant_id = strdup(merchant_id);
    config->secret_key = strdup(SECRET_KEY);
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    free(config->merchant_id);
    free(config->secret_key);
    free(config);
}

void process_payment(PaymentGatewayConfig *config, float amount) {
    printf("Processing payment of $%.2f with merchant ID %s and secret key %s\n",
           amount, config->merchant_id, config->secret_key);
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("merchant_123");
    process_payment(config, 99.99);
    destroy_payment_gateway_config(config);
    return 0;
}