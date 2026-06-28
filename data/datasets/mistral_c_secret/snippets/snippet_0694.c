#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *merchant_id;
    char *api_url;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_payment_gateway_config(const char *merchant_id, const char *api_url) {
    PaymentGatewayConfig *config = malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->merchant_id = strdup(merchant_id);
    if (config->merchant_id == NULL) {
        free(config);
        return NULL;
    }

    config->api_url = strdup(api_url);
    if (config->api_url == NULL) {
        free(config->merchant_id);
        free(config);
        return NULL;
    }

    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    if (config->secret_key == NULL) {
        free(config->api_url);
        free(config->merchant_id);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->merchant_id != NULL) {
            free(config->merchant_id);
        }
        if (config->api_url != NULL) {
            free(config->api_url);
        }
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("merchant123", "https://payment.api.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create Payment Gateway Config\n");
        return 1;
    }

    printf("Payment Gateway Config created with secret key: %s\n", config->secret_key);

    destroy_payment_gateway_config(config);
    return 0;
}