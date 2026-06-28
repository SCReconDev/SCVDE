#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THIRD_PARTY_API_URL "https://api.thirdparty.com/v1"
#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char* url;
    char* bearer_token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_third_party_integration() {
    ThirdPartyIntegration* integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    if (integration == NULL) {
        return NULL;
    }

    integration->url = strdup(THIRD_PARTY_API_URL);
    if (integration->url == NULL) {
        free(integration);
        return NULL;
    }

    integration->bearer_token = getenv(BEARER_TOKEN_ENV_VAR);
    if (integration->bearer_token == NULL) {
        free(integration->url);
        free(integration);
        return NULL;
    }

    return integration;
}

void destroy_third_party_integration(ThirdPartyIntegration* integration) {
    if (integration != NULL) {
        free(integration->url);
        free(integration->bearer_token);
        free(integration);
    }
}

int main() {
    ThirdPartyIntegration* integration = create_third_party_integration();
    if (integration == NULL) {
        fprintf(stderr, "Failed to create third party integration\n");
        return 1;
    }

    printf("Third Party Integration created successfully\n");
    printf("URL: %s\n", integration->url);
    printf("Bearer Token: %s\n", integration->bearer_token);

    destroy_third_party_integration(integration);
    return 0;
}