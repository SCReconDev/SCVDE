#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYMENT_GATEWAY_URL "https://payment.example.com/v1"
#define SECRET_KEY_ENV_VAR "PAYMENT_SECRET_KEY"

typedef struct {
    char *secret_key;
    char *url;
} PaymentGateway;

PaymentGateway* create_gateway() {
    PaymentGateway *gateway = (PaymentGateway*)malloc(sizeof(PaymentGateway));
    gateway->url = strdup(PAYMENT_GATEWAY_URL);
    gateway->secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (gateway->secret_key == NULL) {
        fprintf(stderr, "Error: Secret key not found in environment variables.\n");
        free(gateway->url);
        free(gateway);
        return NULL;
    }
    return gateway;
}

void destroy_gateway(PaymentGateway *gateway) {
    if (gateway != NULL) {
        free(gateway->url);
        free(gateway);
    }
}

int process_payment(PaymentGateway *gateway, float amount) {
    if (gateway == NULL || gateway->secret_key == NULL) {
        return -1;
    }
    printf("Processing payment of $%.2f with secret key: %s\n", amount, gateway->secret_key);
    return 0;
}

int main() {
    PaymentGateway *gateway = create_gateway();
    if (gateway == NULL) {
        return EXIT_FAILURE;
    }
    process_payment(gateway, 100.00);
    destroy_gateway(gateway);
    return EXIT_SUCCESS;
}