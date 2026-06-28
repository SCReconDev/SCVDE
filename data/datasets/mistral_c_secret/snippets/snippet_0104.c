#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "sk_test_4eC39HqLyjWDarjtT1zdp7dc"

typedef struct {
    char *api_key;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *api_key) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_key = strdup(api_key);
    if (config->api_key == NULL) {
        free(config);
        return NULL;
    }

    config->secret_key = strdup(SECRET_KEY);
    if (config->secret_key == NULL) {
        free(config->api_key);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->api_key);
        free(config->secret_key);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("pk_test_TYooMQauvdEDq54NiTphI7jx");
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config\n");
        return 1;
    }

    printf("Payment gateway config created with secret key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}