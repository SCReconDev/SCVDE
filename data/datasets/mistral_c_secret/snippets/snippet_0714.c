#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stripe/stripe.h>

#define SECRET_KEY_ENV_VAR "STRIPE_SECRET_KEY"

typedef struct {
    stripe_secret_key_t *secret_key;
    stripe_account_t *account;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    char *secret_key = getenv(SECRET_KEY_ENV_VAR);
    if (secret_key == NULL) {
        fprintf(stderr, "Stripe secret key not found in environment variables\n");
        free(config);
        return NULL;
    }

    config->secret_key = stripe_secret_key_new(secret_key);
    if (config->secret_key == NULL) {
        fprintf(stderr, "Failed to create Stripe secret key\n");
        free(config);
        return NULL;
    }

    config->account = stripe_account_new(config->secret_key);
    if (config->account == NULL) {
        fprintf(stderr, "Failed to create Stripe account\n");
        stripe_secret_key_free(config->secret_key);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        if (config->account != NULL) {
            stripe_account_free(config->account);
        }
        if (config->secret_key != NULL) {
            stripe_secret_key_free(config->secret_key);
        }
        free(config);
    }
}

void create_payment_intent(PaymentGatewayConfig *config, int amount, const char *currency) {
    if (config == NULL || config->account == NULL) {
        fprintf(stderr, "Invalid payment gateway configuration\n");
        return;
    }

    stripe_payment_intent_params_t *params = stripe_payment_intent_params_new();
    stripe_payment_intent_params_set_amount(params, amount);
    stripe_payment_intent_params_set_currency(params, currency);

    stripe_payment_intent_t *intent = stripe_payment_intent_new(config->account, params);
    if (intent == NULL) {
        fprintf(stderr, "Failed to create payment intent\n");
        stripe_payment_intent_params_free(params);
        return;
    }

    printf("Payment intent created successfully\n");
    stripe_payment_intent_free(intent);
    stripe_payment_intent_params_free(params);
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config();
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway configuration\n");
        return 1;
    }

    create_payment_intent(config, 1000, "usd");
    destroy_payment_gateway_config(config);

    return 0;
}