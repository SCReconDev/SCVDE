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

    const char *secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (secret_key == NULL) {
        fprintf(stderr, "Secret key not found in environment variables.\n");
        free(config->gateway_url);
        free(config);
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    if (config->secret_key == NULL) {
        free(config->gateway_url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->gateway_url);
        free(config->secret_key);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("https://payment.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config.\n");
        return 1;
    }

    printf("Payment Gateway Config created successfully.\n");
    printf("Gateway URL: %s\n", config->gateway_url);
    printf("Secret Key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}