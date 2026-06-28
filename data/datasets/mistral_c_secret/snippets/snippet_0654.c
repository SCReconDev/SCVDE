#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_SECRET_KEY_ENV_VAR "PAYMENT_GATEWAY_SECRET_KEY"

typedef struct {
    char *api_key;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *api_key) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_key = strdup(api_key);
    if (config->api_key == NULL) {
        free(config);
        return NULL;
    }

    config->secret_key = getenv(PAYMENT_GATEWAY_SECRET_KEY_ENV_VAR);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Payment gateway secret key not found in environment variables\n");
        free(config->api_key);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->api_key != NULL) {
            free(config->api_key);
        }
        free(config);
    }
}

int main() {
    const char *api_key = "pk_test_123456789";

    PaymentGatewayConfig *config = create_payment_gateway_config(api_key);

    if (config != NULL) {
        printf("Payment gateway config created successfully\n");
        destroy_payment_gateway_config(config);
    } else {
        fprintf(stderr, "Failed to create payment gateway config\n");
    }

    return 0;
}