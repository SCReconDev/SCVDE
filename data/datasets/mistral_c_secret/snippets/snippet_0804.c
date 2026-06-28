#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SECRET_KEY_LENGTH 100

typedef struct {
    char secret_key[MAX_SECRET_KEY_LENGTH];
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config() {
    PaymentGatewayConfig* config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    const char* secret_key_env = getenv("PAYMENT_SECRET_KEY");
    if (secret_key_env == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set\n");
        free(config);
        return NULL;
    }

    strncpy(config->secret_key, secret_key_env, MAX_SECRET_KEY_LENGTH - 1);
    config->secret_key[MAX_SECRET_KEY_LENGTH - 1] = '\0';

    return config;
}

void process_payment(PaymentGatewayConfig* config, const char* payment_data) {
    printf("Processing payment with secret key: %s\n", config->secret_key);
    printf("Payment data: %s\n", payment_data);
}

void destroy_payment_gateway_config(PaymentGatewayConfig* config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    PaymentGatewayConfig* config = create_payment_gateway_config();
    if (config == NULL) {
        return 1;
    }

    process_payment(config, "payment_data");
    destroy_payment_gateway_config(config);

    return 0;
}