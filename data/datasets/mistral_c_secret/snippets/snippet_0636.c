#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THIRD_PARTY_API_URL "https://api.thirdparty.com/v1/data"

typedef struct {
    char *bearer_token;
    char *url;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_integration() {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->bearer_token = getenv("THIRD_PARTY_BEARER_TOKEN");
    if (integration->bearer_token == NULL) {
        fprintf(stderr, "THIRD_PARTY_BEARER_TOKEN environment variable not set.\n");
        free(integration);
        return NULL;
    }

    integration->url = strdup(THIRD_PARTY_API_URL);
    if (integration->url == NULL) {
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_integration(ThirdPartyIntegration *integration) {
    if (integration != NULL) {
        free(integration->url);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration *integration = create_integration();
    if (integration == NULL) {
        return 1;
    }

    printf("Third-party integration created with bearer token: %s\n", integration->bearer_token);
    destroy_integration(integration);
    return 0;
}