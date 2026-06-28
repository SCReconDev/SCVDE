#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

typedef struct {
    char *api_key;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_config(const char *api_key) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    config->api_key = strdup(api_key);
    config->secret_key = strdup(SECRET_KEY);
    return config;
}

void destroy_config(PaymentGatewayConfig *config) {
    free(config->api_key);
    free(config->secret_key);
    free(config);
}

int main() {
    PaymentGatewayConfig *config = create_config("pk_test_TYooMQauvdEDq54NiTphI7jx");
    printf("Config created with secret key: %s\n", config->secret_key);
    destroy_config(config);
    return 0;
}