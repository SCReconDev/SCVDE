#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com/v1/charge"

typedef struct {
    char *secret_key;
    char *url;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *secret_key) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    if (config->secret_key == NULL) {
        free(config);
        return NULL;
    }

    config->url = strdup(PAYMENT_GATEWAY_URL);
    if (config->url == NULL) {
        free(config->secret_key);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->secret_key);
        free(config->url);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *card_number, const char *amount) {
    if (config == NULL || card_number == NULL || amount == NULL) {
        return -1;
    }

    // Simulate processing payment
    printf("Processing payment of %s with card number %s\n", amount, card_number);
    printf("Using secret key: %s\n", config->secret_key);

    return 0;
}

int main() {
    const char *payment_secret_key = getenv("PAYMENT_SECRET_KEY");
    if (payment_secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(payment_secret_key);
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    const char *card_number = "4111111111111111";
    const char *amount = "100.00";

    if (process_payment(config, card_number, amount) != 0) {
        fprintf(stderr, "Failed to process payment\n");
        destroy_payment_gateway_config(config);
        return 1;
    }

    printf("Payment processed successfully\n");
    destroy_payment_gateway_config(config);

    return 0;
}