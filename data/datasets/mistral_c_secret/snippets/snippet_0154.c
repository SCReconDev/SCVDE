#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_1234567890abcdefghij"

typedef struct {
    char *api_url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_config(const char *api_url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    config->api_url = strdup(api_url);
    config->secret_key = strdup(SECRET_KEY);
    return config;
}

void destroy_config(PaymentGatewayConfig *config) {
    free(config->api_url);
    free(config->secret_key);
    free(config);
}

void process_payment(PaymentGatewayConfig *config, const char *payment_data) {
    printf("Processing payment: %s with secret key: %s\n", payment_data, config->secret_key);
}

int main() {
    PaymentGatewayConfig *config = create_config("https://payments.example.com/api");
    process_payment(config, "payment_data_123");
    destroy_config(config);
    return 0;
}