#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY_ENV_VAR "SECRET_KEY"

typedef struct {
    char *gateway_url;
    char *secret_key;
    char *merchant_id;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *gateway_url, const char *merchant_id) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->gateway_url = strdup(gateway_url);
    if (config->gateway_url == NULL) {
        free(config);
        return NULL;
    }

    config->merchant_id = strdup(merchant_id);
    if (config->merchant_id == NULL) {
        free(config->gateway_url);
        free(config);
        return NULL;
    }

    config->secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Error: Secret key not found in environment variables.\n");
        free(config->gateway_url);
        free(config->merchant_id);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->gateway_url != NULL) {
            free(config->gateway_url);
        }
        if (config->merchant_id != NULL) {
            free(config->merchant_id);
        }
        if (config->secret_key != NULL) {
            free(config->secret_key);
        }
        free(config);
    }
}

int main() {
    const char *gateway_url = "https://payment.example.com";
    const char *merchant_id = "merchant123";

    PaymentGatewayConfig *config = create_payment_gateway_config(gateway_url, merchant_id);

    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config.\n");
        return 1;
    }

    printf("Payment Gateway Config created with gateway URL: %s, merchant ID: %s\n", config->gateway_url, config->merchant_id);
    printf("Secret Key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}