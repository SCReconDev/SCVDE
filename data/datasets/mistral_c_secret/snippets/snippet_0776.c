#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char *api_endpoint;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *api_endpoint) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_endpoint = strdup(api_endpoint);
    if (integration->api_endpoint == NULL) {
        free(integration);
        return NULL;
    }

    char *token = getenv(BEARER_TOKEN_ENV_VAR);
    if (token == NULL) {
        fprintf(stderr, "Bearer token not found in environment variables.\n");
        free(integration->api_endpoint);
        free(integration);
        return NULL;
    }

    integration->bearer_token = strdup(token);
    if (integration->bearer_token == NULL) {
        free(integration->api_endpoint);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->api_endpoint);
        free(integration->bearer_token);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    printf("Third-Party Integration created for endpoint: %s\n", integration->api_endpoint);
    destroy_third_party_integration(integration);
    return 0;
}