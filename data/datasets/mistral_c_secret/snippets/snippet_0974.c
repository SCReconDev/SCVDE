#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY_ENV_VAR "PAYMENT_GATEWAY_SECRET_KEY"

typedef struct {
    char *api_key;
    char *secret_key;
    char *endpoint;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *api_key, const char *endpoint) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_key = strdup(api_key);
    config->endpoint = strdup(endpoint);

    if (config->api_key == NULL || config->endpoint == NULL) {
        free(config->api_key);
        free(config->endpoint);
        free(config);
        return NULL;
    }

    const char *secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (secret_key == NULL) {
        fprintf(stderr, "Error: Payment gateway secret key not found in environment variables.\n");
        free(config->api_key);
        free(config->endpoint);
        free(config);
        return NULL;
    }

    config->secret_key = strdup(secret_key);
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
        free(config->api_key);
        free(config->secret_key);
        free(config->endpoint);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("my-api-key", "https://payment.example.com");
    if (config == NULL) {
        return EXIT_FAILURE;
    }

    printf("Payment gateway configuration created.\n");
    printf("API Key: %s\n", config->api_key);
    printf("Endpoint: %s\n", config->endpoint);

    destroy_payment_gateway_config(config);
    return EXIT_SUCCESS;
}