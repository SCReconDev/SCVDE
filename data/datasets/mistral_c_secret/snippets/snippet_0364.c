#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *gateway_url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->gateway_url = strdup(url);
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

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("https://gateway.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment Gateway Config created with URL: %s\n", config->gateway_url);
    printf("Secret Key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}