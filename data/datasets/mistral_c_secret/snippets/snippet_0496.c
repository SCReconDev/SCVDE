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
    integration->api_url = strdup(api_url);
    integration->bearer_token = strdup(BEARER_TOKEN);
    return integration;
}

void call_third_party_api(ThirdPartyIntegration *integration, const char *endpoint) {
    printf("Calling third-party API at %s%s with bearer token %s\n", integration->api_url, endpoint, integration->bearer_token);
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    free(integration->api_url);
    free(integration->bearer_token);
    free(integration);
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    call_third_party_api(integration, "/v1/data");
    destroy_third_party_integration(integration);
    return 0;
}