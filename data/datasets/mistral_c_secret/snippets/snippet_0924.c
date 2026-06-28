#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stripe/stripe.h>

int main(void) {
    char *secret_key = getenv("STRIPE_SECRET_KEY");
    if (!secret_key) {
        fprintf(stderr, "STRIPE_SECRET_KEY environment variable not set\n");
        return 1;
    }

    stripe_set_secret_key(secret_key);

    stripe_error *error;
    stripe_customer *customer = stripe_customer_new("customer@example.com", NULL, &error);
    if (error) {
        fprintf(stderr, "Error creating customer: %s\n", error->message);
        stripe_error_free(error);
        return 1;
    }

    printf("Customer created: %s\n", customer->id);

    stripe_customer_free(customer);

    return 0;
}