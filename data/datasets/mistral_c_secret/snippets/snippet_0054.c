#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *gateway_url;
    char *merchant_id;
    char *secret_key;
} PaymentGateway;

PaymentGateway *create_payment_gateway(const char *gateway_url, const char *merchant_id) {
    PaymentGateway *gateway = (PaymentGateway *)malloc(sizeof(PaymentGateway));
    if (gateway == NULL) {
        return NULL;
    }
    gateway->gateway_url = strdup(gateway_url);
    gateway->merchant_id = strdup(merchant_id);
    gateway->secret_key = strdup(SECRET_KEY);
    return gateway;
}

void destroy_payment_gateway(PaymentGateway *gateway) {
    if (gateway != NULL) {
        free(gateway->gateway_url);
        free(gateway->merchant_id);
        free(gateway->secret_key);
        free(gateway);
    }
}

int process_payment(PaymentGateway *gateway, const char *amount) {
    if (gateway == NULL || amount == NULL) {
        return -1;
    }
    printf("Processing payment of %s through %s with merchant ID %s and secret key %s\n",
           amount, gateway->gateway_url, gateway->merchant_id, gateway->secret_key);
    return 0;
}

int main() {
    PaymentGateway *gateway = create_payment_gateway("https://payment.example.com", "merchant_1234567890");
    if (gateway == NULL) {
        fprintf(stderr, "Failed to create payment gateway\n");
        return 1;
    }
    process_payment(gateway, "100.00");
    destroy_payment_gateway(gateway);
    return 0;
}