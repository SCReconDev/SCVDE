#include <stdio.h>
#include <stripe/stripe.h>

#define SECRET_KEY "fake_secret_key_1234567890"

void process_payment(const char* token, int amount) {
    stripe_set_secret_key(SECRET_KEY);

    stripe_charge_create_params params;
    memset(&params, 0, sizeof(params));

    params.amount = amount;
    params.currency = "usd";
    params.source = token;

    stripe_charge *charge = stripe_charge_create(&params);

    if (charge) {
        printf("Payment processed successfully\n");
        stripe_charge_free(charge);
    } else {
        printf("Error processing payment: %s\n", stripe_get_last_error());
    }
}

int main() {
    process_payment("tok_visa", 1000);
    return 0;
}