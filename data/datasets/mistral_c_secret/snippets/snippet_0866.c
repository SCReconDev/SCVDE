#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THIRD_PARTY_URL "https://thirdparty.example.com"
#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char *url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->url = strdup(url);
    if (integration->url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Bearer token not found in environment variables.\n");
        free(integration->url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        if (integration->url != NULL) {
            free(integration->url);
        }
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration(THIRD_PARTY_URL);
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration.\n");
        return 1;
    }

    printf("Third-Party Integration created successfully.\n");
    printf("URL: %s\n", integration->url);
    printf("Bearer Token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}