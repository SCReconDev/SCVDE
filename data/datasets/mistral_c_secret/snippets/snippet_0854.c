#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *merchant_id;
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

    config->secret_key = getenv("PAYMENT_GATEWAY_SECRET_KEY");
    if (config->secret_key == NULL) {
        free(config->merchant_id);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->merchant_id != NULL) {
            free(config->merchant_id);
        }
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("merchant123");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment gateway config created for merchant: %s\n", config->merchant_id);
    printf("Secret key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}