#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

typedef struct {
    char *integration_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration(const char *integration_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    integration->integration_url = strdup(integration_url);
    integration->bearer_token = strdup(BEARER_TOKEN);
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    free(integration->integration_url);
    free(integration->bearer_token);
    free(integration);
}

void call_third_party_api(ThirdPartyIntegration *integration, const char *endpoint) {
    printf("Calling third-party API at %s%s with bearer token %s\n", integration->integration_url, endpoint, integration->bearer_token);
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://thirdparty.example.com");
    call_third_party_api(integration, "/data");
    destroy_third_party_integration(integration);
    return 0;
}