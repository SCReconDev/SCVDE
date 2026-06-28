#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *api_key;
    char *merchant_id;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *secret_key, const char *api_key, const char *merchant_id) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    config->api_key = strdup(api_key);
    config->merchant_id = strdup(merchant_id);

    if (config->secret_key == NULL || config->api_key == NULL || config->merchant_id == NULL) {
        free(config->secret_key);
        free(config->api_key);
        free(config->merchant_id);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->secret_key);
        free(config->api_key);
        free(config->merchant_id);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *amount) {
    if (config == NULL || config->secret_key == NULL || config->api_key == NULL || config->merchant_id == NULL) {
        return -1;
    }

    printf("Processing payment of %s with secret key %s, API key %s, and merchant ID %s\n", amount, config->secret_key, config->api_key, config->merchant_id);
    return 0;
}

int main() {
    const char *secret_key = getenv("PAYMENT_SECRET_KEY");
    const char *api_key = getenv("PAYMENT_API_KEY");
    const char *merchant_id = getenv("PAYMENT_MERCHANT_ID");

    if (secret_key == NULL || api_key == NULL || merchant_id == NULL) {
        fprintf(stderr, "Payment gateway environment variables not set\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(secret_key, api_key, merchant_id);
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    if (process_payment(config, "100.00") != 0) {
        fprintf(stderr, "Failed to process payment\n");
        destroy_payment_gateway_config(config);
        return 1;
    }

    destroy_payment_gateway_config(config);
    return 0;
}