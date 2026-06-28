#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com"
#define SECRET_KEY_ENV_VAR "SECRET_KEY"

typedef struct {
    char *url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->url = strdup(url);
    if (config->url == NULL) {
        free(config);
        return NULL;
    }

    config->secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Secret key not found in environment variables.\n");
        free(config->url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->url != NULL) {
            free(config->url);
        }
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config(PAYMENT_GATEWAY_URL);
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config.\n");
        return 1;
    }

    printf("Payment Gateway Config created successfully.\n");
    printf("URL: %s\n", config->url);
    printf("Secret Key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}