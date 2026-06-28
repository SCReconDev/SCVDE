#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *merchant_id;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *merchant_id) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->merchant_id = strdup(merchant_id);
    if (config->merchant_id == NULL) {
        free(config);
        return NULL;
    }

    config->secret_key = strdup(SECRET_KEY);
    if (config->secret_key == NULL) {
        free(config->merchant_id);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->merchant_id);
        free(config->secret_key);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("merchant_123");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return EXIT_FAILURE;
    }

    printf("Payment gateway config created with merchant ID: %s\n", config->merchant_id);
    printf("Secret key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return EXIT_SUCCESS;
}