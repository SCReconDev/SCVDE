#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com"
#define SECRET_KEY_ENV "PAYMENT_SECRET_KEY"

typedef struct {
    char *url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->url = strdup(PAYMENT_GATEWAY_URL);
    config->secret_key = getenv(SECRET_KEY_ENV);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Error: Payment secret key not found in environment variables.\n");
        free(config->url);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->url);
        free(config->secret_key);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, double amount) {
    if (config == NULL || config->secret_key == NULL) {
        return -1;
    }
    printf("Processing payment of %.2f at %s with secret key %s\n", amount, config->url, config->secret_key);
    return 0;
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config();
    if (config == NULL) {
        return 1;
    }
    process_payment(config, 100.00);
    destroy_payment_gateway_config(config);
    return 0;
}