#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY_ENV_VAR "SECRET_KEY"

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
    if (config->gateway_url == NULL) {
        free(config);
        return NULL;
    }

    config->secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Secret key not found in environment variables.\n");
        free(config->gateway_url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->gateway_url);
        free(config);
    }
}

int main() {
    const char *gateway_url = "https://payment.example.com";
    PaymentGatewayConfig *config = create_payment_gateway_config(gateway_url);

    if (config != NULL) {
        printf("Payment Gateway Config created successfully.\n");
        destroy_payment_gateway_config(config);
    } else {
        printf("Failed to create Payment Gateway Config.\n");
    }

    return 0;
}