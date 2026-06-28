#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *api_endpoint;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *api_endpoint) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_endpoint = strdup(api_endpoint);
    if (config->api_endpoint == NULL) {
        free(config);
        return NULL;
    }

    config->secret_key = getenv("PAYMENT_GATEWAY_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "PAYMENT_GATEWAY_SECRET_KEY environment variable not set.\n");
        free(config->api_endpoint);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->api_endpoint != NULL) {
            free(config->api_endpoint);
        }
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

    return 0;
}