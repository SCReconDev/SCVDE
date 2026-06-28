#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

typedef struct {
    char *gateway;
    char *key;
} PaymentGateway;

PaymentGateway* create_gateway(const char *gateway) {
    PaymentGateway *pg = (PaymentGateway*)malloc(sizeof(PaymentGateway));
    pg->gateway = strdup(gateway);
    pg->key = strdup(SECRET_KEY);
    return pg;
}

void destroy_gateway(PaymentGateway *pg) {
    free(pg->gateway);
    free(pg->key);
    free(pg);
}

void process_payment(PaymentGateway *pg, const char *transaction) {
    printf("Processing payment %s through gateway %s with secret key %s\n",
           transaction, pg->gateway, pg->key);
}

int main() {
    PaymentGateway *pg = create_gateway("stripe");
    process_payment(pg, "txn_1234567890");
    destroy_gateway(pg);
    return 0;
}