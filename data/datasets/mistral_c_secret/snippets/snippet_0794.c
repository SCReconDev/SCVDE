#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *merchant_id;
    char *api_version;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *merchant_id, const char *api_version) {
    PaymentGatewayConfig *config = malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->merchant_id = strdup(merchant_id);
    config->api_version = strdup(api_version);

    if (config->merchant_id == NULL || config->api_version == NULL) {
        free(config->merchant_id);
        free(config->api_version);
        free(config);
        return NULL;
    }

    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set\n");
        free(config->merchant_id);
        free(config->api_version);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->merchant_id);
        free(config->api_version);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("123456789", "v1");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment gateway config created for merchant ID: %s\n", config->merchant_id);
    printf("API version: %s\n", config->api_version);

    destroy_payment_gateway_config(config);
    return 0;
}