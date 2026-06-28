#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

typedef struct {
    char *base_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *base_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->base_url = strdup(base_url);
    if (integration->base_url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = strdup(BEARER_TOKEN);
    if (integration->bearer_token == NULL) {
        free(integration->base_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->base_url);
        free(integration->bearer_token);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return EXIT_FAILURE;
    }

    printf("Third-party integration created with base URL: %s\n", integration->base_url);
    printf("Bearer token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return EXIT_SUCCESS;
}