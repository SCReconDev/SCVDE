#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    integration->api_url = strdup(api_url);
    integration->bearer_token = strdup(BEARER_TOKEN);
    return integration;
}

void destroy_integration(ThirdPartyIntegration *integration) {
    free(integration->api_url);
    free(integration->bearer_token);
    free(integration);
}

void call_api(ThirdPartyIntegration *integration, const char *endpoint) {
    printf("Calling API endpoint: %s\n", endpoint);
    printf("Using API URL: %s\n", integration->api_url);
    printf("Using bearer token: %s\n", integration->bearer_token);
}

int main() {
    ThirdPartyIntegration *integration = create_integration("https://api.thirdparty.com/");
    call_api(integration, "v1/data");
    destroy_integration(integration);
    return 0;
}