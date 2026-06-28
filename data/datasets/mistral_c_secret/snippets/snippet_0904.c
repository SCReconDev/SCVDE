#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *api_key;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config(const char *api_key, const char *secret_key) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_key = strdup(api_key);
    config->secret_key = strdup(secret_key);

    if (config->api_key == NULL || config->secret_key == NULL) {
        free(config->api_key);
        free(config->secret_key);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->api_key);
        free(config->secret_key);
        free(config);
    }
}

int process_payment(PaymentGatewayConfig *config, const char *amount, const char *currency, char *response_buffer, size_t buffer_size) {
    if (config == NULL || amount == NULL || currency == NULL || response_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "curl -X POST https://api.paymentgateway.com/charge -H \"Content-Type: application/json\" -H \"Authorization: Bearer %s\" -d '{\"amount\":\"%s\",\"currency\":\"%s\"}'", config->secret_key, amount, currency);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }

    size_t bytes_read = fread(response_buffer, 1, buffer_size - 1, fp);
    response_buffer[bytes_read] = '\0';

    pclose(fp);

    return 0;
}

int main() {
    const char *api_key_env = getenv("PAYMENT_API_KEY");
    const char *secret_key_env = getenv("PAYMENT_SECRET_KEY");

    if (api_key_env == NULL || secret_key_env == NULL) {
        fprintf(stderr, "PAYMENT_API_KEY or PAYMENT_SECRET_KEY environment variable not set.\n");
        return 1;
    }

    PaymentGatewayConfig *config = create_payment_gateway_config(api_key_env, secret_key_env);
    if (config == NULL) {
        fprintf(stderr, "Failed to create payment gateway config.\n");
        return 1;
    }

    char response_buffer[MAX_BUFFER_SIZE];
    if (process_payment(config, "100.00", "USD", response_buffer, sizeof(response_buffer)) != 0) {
        fprintf(stderr, "Failed to process payment.\n");
        destroy_payment_gateway_config(config);
        return 1;
    }

    printf("Payment Response: %s\n", response_buffer);

    destroy_payment_gateway_config(config);

    return 0;
}