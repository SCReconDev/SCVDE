#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "Bearer abcdef1234567890"

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_integration(const char *api_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    integration->api_url = strdup(api_url);
    integration->bearer_token = strdup(BEARER_TOKEN);
    return integration;
}

void destroy_integration(ThirdPartyIntegration *integration) {
    free(integration->api_url);
    free(integration->bearer_token);
    free(integration);
}

void fetch_data(ThirdPartyIntegration *integration) {
    printf("Fetching data from: %s with bearer token: %s\n", integration->api_url, integration->bearer_token);
}

int main() {
    ThirdPartyIntegration *integration = create_integration("https://api.thirdparty.com/data");
    fetch_data(integration);
    destroy_integration(integration);
    return 0;
}