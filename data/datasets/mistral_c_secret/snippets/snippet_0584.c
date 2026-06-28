#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *api_key;
    char *secret_key;
    char *endpoint;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *endpoint) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->endpoint = strdup(endpoint);
    if (config->endpoint == NULL) {
        free(config);
        return NULL;
    }

    config->api_key = getenv("PAYMENT_API_KEY");
    if (config->api_key == NULL) {
        free(config->endpoint);
        free(config);
        return NULL;
    }

    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    if (config->secret_key == NULL) {
        free(config->api_key);
        free(config->endpoint);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->secret_key != NULL) {
            free(config->secret_key);
        }
        if (config->api_key != NULL) {
            free(config->api_key);
        }
        if (config->endpoint != NULL) {
            free(config->endpoint);
        }
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("https://payment.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment gateway config created with endpoint: %s\n", config->endpoint);
    printf("Payment gateway config created with API key: %s\n", config->api_key);

    destroy_payment_gateway_config(config);
    return 0;
}