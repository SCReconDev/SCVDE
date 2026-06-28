#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *publishable_key;
    char *api_version;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set.\n");
        free(config);
        return NULL;
    }

    config->publishable_key = getenv("PAYMENT_PUBLISHABLE_KEY");
    if (config->publishable_key == NULL) {
        fprintf(stderr, "PAYMENT_PUBLISHABLE_KEY environment variable not set.\n");
        free(config);
        return NULL;
    }

    config->api_version = getenv("PAYMENT_API_VERSION");
    if (config->api_version == NULL) {
        fprintf(stderr, "PAYMENT_API_VERSION environment variable not set.\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config();
    if (config == NULL) {
        return EXIT_FAILURE;
    }

    printf("Payment Gateway Config created successfully.\n");
    printf("Publishable Key: %s\n", config->publishable_key);
    printf("API Version: %s\n", config->api_version);

    destroy_payment_gateway_config(config);
    return EXIT_SUCCESS;
}