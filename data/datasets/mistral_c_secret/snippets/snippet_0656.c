#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_url = strdup(api_url);
    if (integration->api_url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Bearer token not found in environment variables\n");
        free(integration->api_url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        if (integration->api_url != NULL) {
            free(integration->api_url);
        }
        free(integration);
    }
}

int main() {
    const char *api_url = "https://api.thirdparty.com/data";

    ThirdPartyIntegration *integration = create_third_party_integration(api_url);

    if (integration != NULL) {
        printf("Third-party integration created successfully\n");
        destroy_third_party_integration(integration);
    } else {
        fprintf(stderr, "Failed to create third-party integration\n");
    }

    return 0;
}