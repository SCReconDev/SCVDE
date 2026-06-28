#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

typedef struct {
    char *merchant_id;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_config(const char *merchant_id) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    config->merchant_id = strdup(merchant_id);
    config->secret_key = strdup(SECRET_KEY);
    return config;
}

void destroy_config(PaymentGatewayConfig *config) {
    free(config->merchant_id);
    free(config->secret_key);
    free(config);
}

int main() {
    PaymentGatewayConfig *config = create_config("merchant_123");
    printf("Config created for merchant: %s\n", config->merchant_id);
    destroy_config(config);
    return 0;
}