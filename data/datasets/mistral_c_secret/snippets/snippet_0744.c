#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *publishable_key;
    char *api_version;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *secret_key) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    if (config->secret_key == NULL) {
        free(config);
        return NULL;
    }

    config->publishable_key = strdup("pk_test_123456789");
    if (config->publishable_key == NULL) {
        free(config->secret_key);
        free(config);
        return NULL;
    }

    config->api_version = strdup("2022-08-01");
    if (config->api_version == NULL) {
        free(config->publishable_key);
        free(config->secret_key);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->api_version);
        free(config->publishable_key);
        free(config->secret_key);
        free(config);
    }
}

int main() {
    const char *secret_key = getenv("PAYMENT_GATEWAY_SECRET_KEY");
    if (secret_key == NULL) {
        fprintf(stderr, "PAYMENT_GATEWAY_SECRET_KEY environment variable not set\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(secret_key);
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment Gateway Config created with secret key: %s\n", config->secret_key);
    printf("Publishable key: %s\n", config->publishable_key);
    printf("API version: %s\n", config->api_version);

    destroy_payment_gateway_config(config);

    return 0;
}