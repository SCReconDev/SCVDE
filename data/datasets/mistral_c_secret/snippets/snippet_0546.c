#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char *integration_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *integration_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->integration_url = strdup(integration_url);
    if (integration->integration_url == NULL) {
        free(integration);
        return NULL;
    }

    char *token = getenv(BEARER_TOKEN_ENV_VAR);
    if (token == NULL) {
        fprintf(stderr, "Bearer token not found in environment variables\n");
        free(integration->integration_url);
        free(integration);
        return NULL;
    }

    integration->bearer_token = strdup(token);
    if (integration->bearer_token == NULL) {
        free(integration->integration_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->integration_url);
        free(integration->bearer_token);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://integration.example.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    printf("Third-Party Integration created with URL: %s\n", integration->integration_url);
    printf("Bearer Token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}