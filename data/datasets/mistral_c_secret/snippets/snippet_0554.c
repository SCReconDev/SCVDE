#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PG_SECRET_KEY_ENV "PG_SECRET_KEY"

typedef struct {
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = getenv(PG_SECRET_KEY_ENV);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Payment gateway secret key not found in environment variables.\n");
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
        fprintf(stderr, "Failed to create payment gateway configuration.\n");
        return 1;
    }

    printf("Payment gateway configuration created successfully.\n");
    printf("Secret Key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}