#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *merchant_id;
    char *secret_key;
} PaymentGateway;

PaymentGateway *create_payment_gateway(const char *merchant_id) {
    PaymentGateway *gateway = (PaymentGateway *)malloc(sizeof(PaymentGateway));
    gateway->merchant_id = strdup(merchant_id);
    gateway->secret_key = strdup(SECRET_KEY);
    return gateway;
}

void destroy_payment_gateway(PaymentGateway *gateway) {
    free(gateway->merchant_id);
    free(gateway->secret_key);
    free(gateway);
}

int main() {
    PaymentGateway *gateway = create_payment_gateway("merchant_123");
    printf("Payment gateway created with secret key: %s\n", gateway->secret_key);
    destroy_payment_gateway(gateway);
    return 0;
}