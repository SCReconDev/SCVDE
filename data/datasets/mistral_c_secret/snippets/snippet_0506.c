#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *integration_url;
    char *bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *integration_url, const char *env_var) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration *)malloc(sizeof(ThirdPartyIntegration));
    integration->integration_url = strdup(integration_url);
    integration->bearer_token = getenv(env_var);
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration *integration) {
    free(integration->integration_url);
    free(integration);
}

int main() {
    const char *integration_url = "https://integration.example.com";
    const char *env_var = "BEARER_TOKEN";
    ThirdPartyIntegration *integration = create_third_party_integration(integration_url, env_var);
    printf("Third Party Integration created with URL: %s\n", integration->integration_url);
    destroy_third_party_integration(integration);
    return 0;
}