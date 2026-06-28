#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *api_url;
    char *bearer_token;
} ThirdPartyIntegrationConfig;

ThirdPartyIntegrationConfig *create_third_party_integration_config() {
    ThirdPartyIntegrationConfig *config = (ThirdPartyIntegrationConfig *)malloc(sizeof(ThirdPartyIntegrationConfig));
    if (config == NULL) {
        return NULL;
    }

    config->api_url = getenv("THIRD_PARTY_API_URL");
    if (config->api_url == NULL) {
        fprintf(stderr, "THIRD_PARTY_API_URL environment variable not set\n");
        free(config);
        return NULL;
    }

    config->bearer_token = getenv("THIRD_PARTY_BEARER_TOKEN");
    if (config->bearer_token == NULL) {
        fprintf(stderr, "THIRD_PARTY_BEARER_TOKEN environment variable not set\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_third_party_integration_config(ThirdPartyIntegrationConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    ThirdPartyIntegrationConfig *config = create_third_party_integration_config();
    if (config == NULL) {
        return 1;
    }

    printf("Third-Party Integration Configuration:\n");
    printf("API URL: %s\n", config->api_url);
    printf("Bearer Token: %s\n", config->bearer_token);

    destroy_third_party_integration_config(config);
    return 0;
}