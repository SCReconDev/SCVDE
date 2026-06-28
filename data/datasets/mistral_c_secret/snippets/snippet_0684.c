#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *api_endpoint;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    char *key = getenv("PAYMENT_GATEWAY_SECRET_KEY");
    if (key == NULL) {
        fprintf(stderr, "PAYMENT_GATEWAY_SECRET_KEY environment variable not set\n");
        free(config);
        return NULL;
    }

    char *endpoint = getenv("PAYMENT_GATEWAY_API_ENDPOINT");
    if (endpoint == NULL) {
        fprintf(stderr, "PAYMENT_GATEWAY_API_ENDPOINT environment variable not set\n");
        free(config);
        return NULL;
    }

    config->secret_key = strdup(key);
    if (config->secret_key == NULL) {
        free(config);
        return NULL;
    }

    config->api_endpoint = strdup(endpoint);
    if (config->api_endpoint == NULL) {
        free(config->secret_key);
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
        if (config->api_endpoint != NULL) {
            free(config->api_endpoint);
        }
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *payment_data, char *response_buffer, size_t buffer_size) {
    if (config == NULL || payment_data == NULL || response_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    // Simulate processing payment
    snprintf(response_buffer, buffer_size, "Payment processed for %s", payment_data);

    return 0;
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config();
    if (config == NULL) {
        return 1;
    }

    char response[1024];
    if (process_payment(config, "user123", response, 1024) != 0) {
        fprintf(stderr, "Failed to process payment\n");
        destroy_payment_gateway_config(config);
        return 1;
    }

    printf("Payment Response: %s\n", response);

    destroy_payment_gateway_config(config);
    return 0;
}