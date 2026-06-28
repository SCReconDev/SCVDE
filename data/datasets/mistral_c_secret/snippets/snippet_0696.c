#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *bearer_token;
    char *api_url;
} ThirdPartyIntegration;

ThirdPartyIntegration *create_third_party_integration(const char *api_url) {
    ThirdPartyIntegration *integration = malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->api_url = strdup(api_url);
    if (integration->api_url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv("BEARER_TOKEN");
    if (integration->bearer_token == NULL) {
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
    ThirdPartyIntegration *integration = create_third_party_integration("https://api.thirdparty.com");
    if (integration == NULL) {
        fprintf(stderr, "Failed to create Third Party Integration\n");
        return 1;
    }

    printf("Third Party Integration created with bearer token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}