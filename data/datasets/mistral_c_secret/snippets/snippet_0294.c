#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

typedef struct {
    char *api_key;
    char *secret_key;
    char *endpoint;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *api_key, const char *endpoint) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_key = strdup(api_key);
    config->secret_key = strdup(SECRET_KEY);
    config->endpoint = strdup(endpoint);

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->api_key);
        free(config->secret_key);
        free(config->endpoint);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("pk_test_TYooMQauvdEDq54NiTphI7jx", "https://api.stripe.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment Gateway Config created with secret key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}