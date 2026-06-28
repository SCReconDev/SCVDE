#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *api_key;
    char *merchant_id;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *secret_key, const char *api_key, const char *merchant_id) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    if (config->secret_key == NULL) {
        free(config);
        return NULL;
    }

    config->api_key = strdup(api_key);
    if (config->api_key == NULL) {
        free(config->secret_key);
        free(config);
        return NULL;
    }

    config->merchant_id = strdup(merchant_id);
    if (config->merchant_id == NULL) {
        free(config->secret_key);
        free(config->api_key);
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

int process_payment(PaymentGatewayConfig *config, const char *card_number, const char *expiry_date, const char *cvv) {
    if (config == NULL || card_number == NULL || expiry_date == NULL || cvv == NULL) {
        return -1;
    }

    printf("Processing payment with:\n");
    printf("Secret Key: %s\n", config->secret_key);
    printf("API Key: %s\n", config->api_key);
    printf("Merchant ID: %s\n", config->merchant_id);
    printf("Card Number: %s\n", card_number);
    printf("Expiry Date: %s\n", expiry_date);
    printf("CVV: %s\n", cvv);

    return 0;
}

int main() {
    const char *secret_key = getenv("SECRET_KEY");
    if (secret_key == NULL) {
        fprintf(stderr, "SECRET_KEY environment variable not set\n");
        return 1;
    }

    const char *api_key = getenv("API_KEY");
    if (api_key == NULL) {
        fprintf(stderr, "API_KEY environment variable not set\n");
        return 1;
    }

    const char *merchant_id = getenv("MERCHANT_ID");
    if (merchant_id == NULL) {
        fprintf(stderr, "MERCHANT_ID environment variable not set\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(secret_key, api_key, merchant_id);
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    process_payment(config, "4111111111111111", "12/25", "123");

    destroy_payment_gateway_config(config);

    return 0;
}