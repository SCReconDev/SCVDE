#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char *api_endpoint;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *api_endpoint) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_endpoint = strdup(api_endpoint);
    if (integration->api_endpoint == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Bearer token not found in environment variables.\n");
        free(integration->api_endpoint);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->api_endpoint);
        free(integration);
    }
}

int main() {
    const char *api_endpoint = "https://api.thirdparty.com";
    ThirdPartyIntegration *integration = create_third_party_integration(api_endpoint);

    if (integration != NULL) {
        printf("Third Party Integration created successfully.\n");
        destroy_third_party_integration(integration);
    } else {
        printf("Failed to create Third Party Integration.\n");
    }

    return 0;
}