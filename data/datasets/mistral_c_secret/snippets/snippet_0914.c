#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *publishable_key;
    char *api_version;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *secret_key, const char *publishable_key, const char *api_version) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->secret_key = strdup(secret_key);
    config->publishable_key = strdup(publishable_key);
    config->api_version = strdup(api_version);
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    free(config->secret_key);
    free(config->publishable_key);
    free(config->api_version);
    free(config);
}

void process_payment(PaymentGatewayConfig *config, const char *amount) {
    printf("Processing payment of %s\n", amount);
    printf("Using secret key: %s\n", config->secret_key);
    printf("Using publishable key: %s\n", config->publishable_key);
    printf("API version: %s\n", config->api_version);
}

int main() {
    const char *payment_secret_key = getenv("PAYMENT_SECRET_KEY");
    if (payment_secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(payment_secret_key, "pk_test_example", "2023-01-01");
    process_payment(config, "$100.00");
    destroy_payment_gateway_config(config);

    return 0;
}