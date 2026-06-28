#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *secret_key;
    char *merchant_id;
    char *currency;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *merchant_id, const char *currency) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->merchant_id = strdup(merchant_id);
    config->currency = strdup(currency);
    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    if (config->secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set\n");
        free(config->merchant_id);
        free(config->currency);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->merchant_id);
        free(config->currency);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config("123456", "USD");
    if (config == NULL) {
        return 1;
    }
    printf("Payment gateway config created for merchant: %s\n", config->merchant_id);
    destroy_payment_gateway_config(config);
    return 0;
}