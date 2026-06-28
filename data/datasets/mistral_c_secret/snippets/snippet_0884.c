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
    config->secret_key = getenv("PAYMENT_GATEWAY_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "PAYMENT_GATEWAY_SECRET_KEY environment variable not set\n");
        free(config->api_endpoint);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->api_endpoint);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *payment_data) {
    printf("Processing payment with secret key: %s\n", config->secret_key);
    printf("Payment data: %s\n", payment_data);
    return 0;
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("https://api.paymentgateway.com/v1/payments");
    if (config == NULL) {
        return 1;
    }

    process_payment(config, "{\"amount\": 100, \"currency\": \"USD\"}");

    destroy_payment_gateway_config(config);
    return 0;
}