#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *gateway_url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *gateway_url, const char *env_var) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    config->gateway_url = strdup(gateway_url);
    config->secret_key = getenv(env_var);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    free(config->gateway_url);
    free(config);
}

int main() {
    const char *gateway_url = "https://payment.example.com";
    const char *env_var = "PAYMENT_SECRET_KEY";
    PaymentGatewayConfig *config = create_payment_gateway_config(gateway_url, env_var);
    printf("Payment Gateway Config created with URL: %s\n", config->gateway_url);
    destroy_payment_gateway_config(config);
    return 0;
}