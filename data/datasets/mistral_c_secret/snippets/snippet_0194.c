#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *gateway_url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_config(const char *gateway_url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->gateway_url = strdup(gateway_url);
    config->secret_key = strdup(SECRET_KEY);
    return config;
}

void destroy_config(PaymentGatewayConfig *config) {
    free(config->gateway_url);
    free(config->secret_key);
    free(config);
}

void process_payment(PaymentGatewayConfig *config, const char *payment_data) {
    printf("Processing payment: %s\n", payment_data);
    printf("Using gateway URL: %s\n", config->gateway_url);
    printf("Using secret key: %s\n", config->secret_key);
}

int main() {
    PaymentGatewayConfig *config = create_config("https://gateway.example.com/");
    process_payment(config, "payment_data_1234567890");
    destroy_config(config);
    return 0;
}