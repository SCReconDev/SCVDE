#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *api_key;
    char *merchant_id;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_key = getenv("PAYMENT_API_KEY");
    if (config->api_key == NULL) {
        fprintf(stderr, "PAYMENT_API_KEY environment variable not set\n");
        free(config);
        return NULL;
    }

    config->merchant_id = getenv("PAYMENT_MERCHANT_ID");
    if (config->merchant_id == NULL) {
        fprintf(stderr, "PAYMENT_MERCHANT_ID environment variable not set\n");
        free(config);
        return NULL;
    }

    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set\n");
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
        return 1;
    }

    printf("Payment Gateway Configuration:\n");
    printf("API Key: %s\n", config->api_key);
    printf("Merchant ID: %s\n", config->merchant_id);
    printf("Secret Key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}