#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *api_url;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *secret_key, const char *api_url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = strdup(secret_key);
    if (config->secret_key == NULL) {
        free(config);
        return NULL;
    }

    config->api_url = strdup(api_url);
    if (config->api_url == NULL) {
        free(config->secret_key);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->secret_key);
        free(config->api_url);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *payment_data) {
    if (config == NULL || payment_data == NULL) {
        return -1;
    }

    // Simulate payment processing
    printf("Processing payment with secret key: %s\n", config->secret_key);
    printf("Payment data: %s\n", payment_data);

    // In a real implementation, you would use a library to make the HTTP request
    // to the payment gateway API.

    return 0;
}

int main() {
    const char *secret_key = getenv("PAYMENT_GATEWAY_SECRET_KEY");
    if (secret_key == NULL) {
        fprintf(stderr, "PAYMENT_GATEWAY_SECRET_KEY environment variable not set.\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(secret_key, "https://payment.example.com/api");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config.\n");
        return 1;
    }

    if (process_payment(config, "{\"amount\": 100, \"currency\": \"USD\"}") != 0) {
        fprintf(stderr, "Failed to process payment.\n");
        destroy_payment_gateway_config(config);
        return 1;
    }

    destroy_payment_gateway_config(config);

    return 0;
}