#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_SECRET_KEY_ENV_VAR "PAYMENT_GATEWAY_SECRET_KEY"

typedef struct {
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    char *secret_key = getenv(PAYMENT_GATEWAY_SECRET_KEY_ENV_VAR);

    if (secret_key == NULL) {
        fprintf(stderr, "Error: Payment gateway secret key not found in environment variables.\n");
        free(config);
        return NULL;
    }

    config->secret_key = strdup(secret_key);

    if (config->secret_key == NULL) {
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->secret_key);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config();
    if (config == NULL) {
        return 1;
    }

    printf("Payment Gateway Config created successfully.\n");
    printf("Secret Key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}