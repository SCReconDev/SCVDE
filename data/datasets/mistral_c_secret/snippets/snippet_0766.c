#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THIRD_PARTY_URL "https://api.thirdparty.com"
#define BEARER_TOKEN_ENV "THIRD_PARTY_BEARER_TOKEN"

typedef struct {
    char *url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration() {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    integration->url = strdup(THIRD_PARTY_URL);
    integration->bearer_token = getenv(BEARER_TOKEN_ENV);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Error: Bearer token not found in environment variables.\n");
        free(integration->url);
        free(integration);
        return NULL;
    }
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->url);
        free(integration->bearer_token);
        free(integration);
    }
}

int call_third_party_api(ThirdPartyIntegration *integration, const char *endpoint) {
    if (integration == NULL || integration->bearer_token == NULL) {
        return -1;
    }
    printf("Calling third-party API at %s/%s with bearer token %s\n", integration->url, endpoint, integration->bearer_token);
    return 0;
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration();
    if (integration == NULL) {
        return 1;
    }
    call_third_party_api(integration, "data");
    destroy_third_party_integration(integration);
    return 0;
}