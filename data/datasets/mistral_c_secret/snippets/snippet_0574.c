#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com/v1/charge"
#define SECRET_KEY_ENV_VAR "SECRET_KEY"

typedef struct {
    char* url;
    char* secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config() {
    PaymentGatewayConfig* config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->url = strdup(PAYMENT_GATEWAY_URL);
    config->secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Error: Secret key not found in environment variables.\n");
        free(config->url);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig* config) {
    if (config != NULL) {
        free(config->url);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig* config, const char* payment_data) {
    if (config == NULL || config->secret_key == NULL) {
        return -1;
    }
    printf("Processing payment with secret key %s...\n", config->secret_key);
    // Actual payment processing would go here
    return 0;
}

int main() {
    PaymentGatewayConfig* config = create_payment_gateway_config();
    if (config == NULL) {
        return 1;
    }
    process_payment(config, "test_payment_data");
    destroy_payment_gateway_config(config);
    return 0;
}