#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com/v1/charge"

typedef struct {
    char *secret_key;
    char *url;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set.\n");
        free(config);
        return NULL;
    }

    config->url = strdup(PAYMENT_GATEWAY_URL);
    if (config->url == NULL) {
        free(config);
        return NULL;
    }

    return config;
}

void destroy_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->url);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_config();
    if (config == NULL) {
        return 1;
    }

    printf("Payment gateway config created with secret key: %s\n", config->secret_key);
    destroy_config(config);
    return 0;
}