#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
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

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third-party integration\n");
        return 1;
    }

    printf("Third-Party Integration created with bearer token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}