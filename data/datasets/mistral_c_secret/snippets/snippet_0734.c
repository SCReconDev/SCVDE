#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com/api"

typedef struct {
    char *secret_key;
    char *base_url;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *secret_key, const char *base_url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    config->base_url = strdup(base_url);

    if (config->secret_key == NULL || config->base_url == NULL) {
        free(config->secret_key);
        free(config->base_url);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->secret_key);
        free(config->base_url);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *payment_data) {
    if (config == NULL || payment_data == NULL) {
        return -1;
    }

    printf("Processing payment with secret key: %s\n", config->secret_key);
    printf("Payment data: %s\n", payment_data);

    return 0;
}

int main() {
    const char *secret_key = getenv("PAYMENT_SECRET_KEY");
    if (secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set.\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(secret_key, PAYMENT_GATEWAY_URL);
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway configuration.\n");
        return 1;
    }

    process_payment(config, "{\"amount\": 100, \"currency\": \"USD\"}");

    destroy_payment_gateway_config(config);

    return 0;
}