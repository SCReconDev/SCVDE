#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *gateway_url;
    char *secret_key;
} PaymentGatewayConfig;

PaymentGatewayConfig *create_config(const char *gateway_url) {
    PaymentGatewayConfig *config = (PaymentGatewayConfig *)malloc(sizeof(PaymentGatewayConfig));
    if (config == NULL) {
        return NULL;
    }
    config->gateway_url = strdup(gateway_url);
    config->secret_key = getenv("SECRET_KEY");
    if (config->secret_key == NULL) {
        free(config->gateway_url);
        free(config);
        return NULL;
    }
    return config;
}

void destroy_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config->gateway_url);
        free(config->secret_key);
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_config("https://gateway.example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create config\n");
        return 1;
    }
    printf("Config created with secret key: %s\n", config->secret_key);
    destroy_config(config);
    return 0;
}