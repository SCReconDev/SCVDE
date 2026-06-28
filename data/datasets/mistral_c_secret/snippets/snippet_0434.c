#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

typedef struct {
    char *api_key;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *api_key) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->api_key = strdup(api_key);
    config->secret_key = strdup(SECRET_KEY);
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    free(config->api_key);
    free(config->secret_key);
    free(config);
}

int process_payment(PaymentGatewayConfig *config, const char *payment_details) {
    printf("Processing payment with API key %s and secret key %s\n", config->api_key, config->secret_key);
    return 0;
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("pk_test_TYooMQauM0iEzM3QqUjTY");
    process_payment(config, "payment_details");
    destroy_payment_gateway_config(config);
    return 0;
}