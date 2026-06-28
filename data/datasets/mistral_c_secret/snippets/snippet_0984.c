#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com/v1"
#define SECRET_KEY_ENV "SECRET_KEY"

typedef struct {
    char *url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->url = strdup(PAYMENT_GATEWAY_URL);
    if (config->url == NULL) {
        free(config);
        return NULL;
    }

    char *secret_key = getenv(SECRET_KEY_ENV);
    if (secret_key == NULL) {
        free(config->url);
        free(config);
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    if (config->secret_key == NULL) {
        free(config->url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->url);
        free(config->secret_key);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config();
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment Gateway Config created with URL: %s and Secret Key: %s\n", config->url, config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}