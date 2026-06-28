#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"

typedef struct {
    char *base_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *base_url) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    integration->base_url = strdup(base_url);
    integration->bearer_token = strdup(BEARER_TOKEN);
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    free(integration->base_url);
    free(integration->bearer_token);
    free(integration);
}

void call_third_party_api(ThirdPartyIntegration *integration, const char *endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "%s%s", integration->base_url, endpoint);
    printf("Calling third-party API at: %s with token: %s\n", url, integration->bearer_token);
}

int main() {
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com/v1/");
    call_third_party_api(integration, "data");
    destroy_third_party_integration(integration);
    return 0;
}