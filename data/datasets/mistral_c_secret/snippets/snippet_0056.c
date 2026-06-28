#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

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
    integration->bearer_token = strdup(BEARER_TOKEN);
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->api_url);
        free(integration->bearer_token);
        free(integration);
    }
}

int call_third_party_api(ThirdPartyIntegration *integration, const char *endpoint) {
    if (integration == NULL || endpoint == NULL) {
        return -1;
    }
    printf("Calling third-party API at %s%s with bearer token %s\n",
           integration->api_url, endpoint, integration->bearer_token);
    return 0;
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }
    call_third_party_api(integration, "/data");
    destroy_third_party_integration(integration);
    return 0;
}